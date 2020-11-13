#include <napi.h>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std; 
const int RUN = 64; 
  
void insertionSort(vector<double>& arr, int& left, const int& right) { 
  for (int i = left + 1; i <= right; i++) 
  { 
    double temp = arr[i]; 
    int j = i - 1; 

    while (j >= left && arr[j] > temp) { 
      arr[j+1] = arr[j]; 
      j--; 
    }

    arr[j+1] = temp;
  } 
} 

void merge(vector<double>& arr, int& l, int& m, int& r) {
  int len1 = m - l + 1, len2 = r - m; 
  vector<double> left;
  vector<double> right;

  for (int i = 0; i < len1; i++) {
    left.push_back(arr[l + i]); 
  }

  for (int i = 0; i < len2; i++) {
    right.push_back(arr[m + 1 + i]);
  }

  int i = 0; 
  int j = 0; 
  int k = l; 

  while (i < len1 && j < len2) { 
    if (left[i] <= right[j]) { 
      arr[k] = left[i]; 
      i++; 
    } 
    else { 
      arr[k] = right[j]; 
      j++; 
    }

    k++; 
  } 
  while (i < len1) { 
    arr[k] = left[i]; 
    k++; 
    i++; 
  }
  while (j < len2) { 
    arr[k] = right[j]; 
    k++; 
    j++; 
  }
} 

void timSort(vector<double>& arr, const int& n) {
  for (int i = 0; i < n; i+=RUN) {
    insertionSort(arr, i, min((i+31), (n-1)));
  }
  for (int size = RUN; size < n; size = 2*size) { 
    for (int left = 0; left < n; left += 2*size) {
      int mid = left + size - 1; 
      int right = min((left + 2*size - 1), (n-1)); 

      merge(arr, left, mid, right); 
    } 
  } 
}


Napi::Array Sort(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  const Napi::Array inputArray = info[0].As<Napi::Array>();

  unsigned int inputLength = inputArray.Length();  

  vector<double> array;
  unsigned int i;

  for (i = 0; i < inputLength; i++) {
    double value = inputArray[i].As<Napi::Number>();

    array.push_back(value);
  }

  int n = array.size();

  timSort(array, n);

  Napi::Array outputArray = Napi::Array::New(env, inputLength);

  for (i = 0; i < inputLength; i++) {
    outputArray[i] = Napi::Number::New(env, array[i]);
  }
  
  return outputArray;
}

Napi::Array SortBuffer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  const Napi::Float64Array inputArray = info[0].As<Napi::Float64Array>();

  unsigned int inputLength = inputArray.ElementLength() / sizeof(double);

  vector<double> array(inputArray.Data(), inputArray.Data() + inputLength);

  int n = array.size();

  timSort(array, n);

  Napi::Array outputArray = Napi::Array::New(env, inputLength);

  for (unsigned int i = 0; i < inputLength; i++) {
    outputArray[i] = Napi::Number::New(env, array[i]);
  }
  
  return outputArray;
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "sort"), Napi::Function::New(env, Sort));
  exports.Set(Napi::String::New(env, "sortBuffer"), Napi::Function::New(env, SortBuffer));
  return exports;
};

NODE_API_MODULE(timsort, init);