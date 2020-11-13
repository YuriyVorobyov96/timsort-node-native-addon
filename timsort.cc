#include <napi.h>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std; 
const int RUN = 32; 
  
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

  cout << 11111 << endl;

  for (int i = 0; i < len1; i++) {
    left.push_back(arr[l + i]); 
  }

  cout << 22222 << endl;

  for (int i = 0; i < len2; i++) {
    right.push_back(arr[m + 1 + i]);
  }

  cout << 3333 << endl;

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

  // const Napi::Array inputArray = info[0].As<Napi::Array>();

  const Napi::Float64Array inputArray = info[0].As<Napi::Float64Array>();

  // Napi::Buffer<double> buffer = info[0].As<Napi::Buffer<double>>();

  // unsigned int length = inputArray.Length();  
  unsigned int inputLength = inputArray.ElementLength() / sizeof(double);
  // vector<int> array = {1,2,3};
  unsigned int i;

  // double (*arrrrrr)[inputLength] = (double (*)[inputLength])inputArray.Data();

  vector<double> array(inputArray.Data(), inputArray.Data() + inputLength);

  // for (const auto& x : vuc) {
  //   cout << x << " ";
  // }

  // cout << endl;

  // cout << "asdasdsada" << endl;
  // cout << inputArray[0] << endl;
  // cout << inputArray[1] << endl;
  // cout << inputArray[2] << endl;
  // cout << "asdasdsada 2" << endl;

  cout << "length: " << inputLength << endl;

  // for (i = 0; i < length; i++) {
  //   int value = inputArray[i].As<Napi::Number>();

  //   array.push_back(value);
  // }

  int n = array.size();

  timSort(array, n);

  Napi::Array outputArray = Napi::Array::New(env, inputLength);

  for (i = 0; i < inputLength; i++) {
    outputArray[i] = Napi::Number::New(env, array[i]);
  }
  
  return outputArray;
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "sort"), Napi::Function::New(env, Sort));
  return exports;
};

NODE_API_MODULE(timsort, init);