#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
#include <pthread.h>
#include <math.h>
using namespace std;
using namespace chrono;

// Global variables
int K;
int N;
int n;
vector<vector<int>> sudoko; // In this vector array the sudoko is stored

struct Data
{
  int tno;
  string type;
};
typedef struct Data datak;

struct Return_for_single_check
{
  string str; // This stores the log data of the single check
  bool valid;
};
typedef struct Return_for_single_check return_single;

struct Return_for_full_thread
{
  vector<string> a; // This vector stores all the logs by a thread
  bool valid;       // This variable stores the output check of the full thread .. i.e combining the effect of all the returns of checks
};
typedef struct Return_for_full_thread return_full;

// The following function checks if the newly added values already exists or not
bool check_if_present(int *check_value, int index, int value)
{
  bool ret = false;
  for (int i = 0; i < index; i++)
  {
    if (check_value[i] == value)
    {
      ret = true;
      break;
    }
  }
  return ret;
}

// The following functions checks if the given row/column/grid is valid/not
return_single check_given_values(int I, int J, int tno, string type)
{
  int check_values[N];
  int check = 1;
  int index = 0;
  int number = 0; // This variable stores the value of the number row/column/grid
  if (type == "row")
  {
    number = I + 1;
    for (int j = 0; j < N; j++)
    {
      if (check_if_present(check_values, index, sudoko.at(I).at(j)))
      {
        check = 0;
        break;
      }
      else
      {
        check_values[index] = sudoko[I][j];
        index++;
      }
    }
  }
  else if (type == "column")
  {
    number = J + 1;
    for (int i = 0; i < N; i++)
    {
      if (check_if_present(check_values, index, sudoko[i][J]))
      {
        check = 0;
        break;
      }
      else
      {
        check_values[index] = sudoko[i][J];
        index++;
      }
    }
  }
  else if (type == "grid")
  {
    number = J / n + 1 + I;
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (check_if_present(check_values, index, sudoko[I + i][J + j]))
        {
          check = 0;
          break;
        }
        else
        {
          check_values[index] = sudoko[I + i][J + j];
          index++;
        }
      }
    }
  }
  return_single r;
  string str ;
  str = "Thread " + to_string(tno) + " checks " + type + " " + to_string(number) + " and is ";
  if (check == 0)
  {
    str += "invalid";
    r.valid = false;
  }
  else
  {
    str += "valid";
    r.valid = true;
  }
  r.str = str;
  return r;
}

// The following function schedules task to the thread

void *func(void *param)
{
  datak *dat = (datak *)param;
  return_full *ret = (return_full *)calloc(1, sizeof(return_full));
  ret->valid = true;
  if (dat->type == "row")
  {
    for (int I = dat->tno - 1; I < N; I += K)
    {
      return_single r = check_given_values(I, 0, dat->tno, dat->type);
      ret->a.push_back(r.str);
      ret->valid = ret->valid && r.valid;
    }
  }
  else if (dat->type == "column")
  {
    for (int J = dat->tno - 1; J < N; J += K)
    {
      return_single r = check_given_values(0, J, dat->tno, dat->type);
      ret->a.push_back(r.str);
      ret->valid = ret->valid && r.valid;
    }
  }
  else if (dat->type == "grid")
  {
    int I[N]; // x[k] represents i value of kth grid
    int J[N]; // y[k] represents j value of kth grid
    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n; j++)
      {
        I[n * j + i] = n * j;
        J[n * j + i] = n * i;
      }
    }

    for (int grid_no = dat->tno; grid_no <= N; grid_no += K)
    {
      return_single r = check_given_values(I[grid_no - 1], J[grid_no - 1], dat->tno, dat->type);
      ret->a.push_back(r.str);
      ret->valid = ret->valid && r.valid;
    }
  }

  return (void *)ret;
}

int main()
{

  auto start = high_resolution_clock::now(); // Clock starts
  ifstream input;
  input.open("input.txt");
  input >> K >> N;
  n = (int)pow(N, 1.0 / 2);
  for (int i = 0; i < N; i++)
  {
    vector<int> temp;
    for (int j = 0; j < N; j++)
    {
      int val = 0;
      input >> val;
      temp.push_back(val);
    }
    sudoko.push_back(temp);
  }

  pthread_t tid[K]; // Taking array of threads
  pthread_attr_t attr;
  pthread_attr_init(&attr); // Setting default value of attribute

  bool sudoko_check = true;

  return_full *temp = NULL;
  return_full all[3 * K];
  
  // For rows
  for (int i = 0; i < K; i++)
  {
    datak *dat = (datak *)calloc(1, sizeof(datak));
    dat->tno = i + 1;
    dat->type = "row";
    pthread_create(&tid[i], &attr, func, dat);
  }
  // Stores row wise output
  for (int i = 0; i < K; i++)
  {
    pthread_join(tid[i], (void **)&temp);
    all[i] = temp[0];
    sudoko_check = sudoko_check && temp[0].valid;
  }

  // For column
  for (int i = 0; i < K; i++)
  {
    datak *dat = (datak *)calloc(1, sizeof(datak));
    dat->tno = i + 1;
    dat->type = "column";
    pthread_create(&tid[i], &attr, func, dat);
  }

  // Stores column wise output
  for (int i = 0; i < K; i++)
  {
    pthread_join(tid[i], (void **)&temp);
    all[i + K] = temp[0];

    sudoko_check = sudoko_check && temp[0].valid;
  }

  // For grid
  for (int i = 0; i < K; i++)
  {
    datak *dat = (datak *)calloc(1, sizeof(datak));
    dat->tno = i + 1;
    dat->type = "grid";
    pthread_create(&tid[i], &attr, func, dat);
  }

  // Stores grid wise output
  for (int i = 0; i < K; i++)
  {
    pthread_join(tid[i], (void **)&temp);
    all[i + 2 * K] = temp[0];

    sudoko_check = sudoko_check && temp[0].valid;
  }

  auto stop = high_resolution_clock::now();
  auto time = duration_cast<microseconds>(stop - start);
  cout << to_string((double)(time.count())) << endl;

  // Writing to output file
  ofstream op;
  op.open("output_pthread.txt");
  if (sudoko_check)
    op << "The Sudoku is valid" << endl;
  else
    op << "The Sudoku is invalid" << endl;
  op << "The time of execution of the program is : " << to_string((double)(time.count())) << endl;
  op << endl;
  op << "Log : " << endl;
  for (int i = 0; i < 3 * K; i++)
  {
    return_full z;
    z = all[i];
    for (int j = 0; j < z.a.size(); j++)
    {
      op << z.a[j] << endl;
    }
  }
  return 0;
}
