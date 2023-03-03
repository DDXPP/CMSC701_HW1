#include "libsais64.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <array>
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/utility.hpp>
#include <cereal/access.hpp>
#include <cereal/archives/binary.hpp>
using namespace std;

void arg_warning() {
  cout << "Please enter the arguments in the following order:\n";
  cout << "./buildsa --preftab <k> reference_path output\n";
  cout << "(Note that '--preftab <k>' is optional.)\n";
}

void arg_num_warning(int argc) {
  cout << "You have entered " << (argc-1) << " arguments, ";
  cout << "but only 2 or 4 arguments are accepted.\n";
  arg_warning();
}

void print_map(std::unordered_map<string, pair<int, int>> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": (" << pair.second.first << ", " << pair.second.second << ")}\n";
    }
}


int main(int argc, char* argv[]) {
  if (argc != 3 && argc != 5) {
    arg_num_warning(argc);
    exit(1);
  }

  //------------------Args------------------
  int64_t arg_k = 0;
  string arg_preftab = "--preftab";
  string arg_reference_path;
  string arg_output;

  if (argc == 3) {
    arg_reference_path = argv[1];
    arg_output = argv[2];
  }
  else { // argc == 5
    if (argv[1] != arg_preftab || stoi(argv[2]) < 1) {
      arg_warning();
      exit(1);
    } 
    arg_k = stoi(argv[2]);
    arg_reference_path = argv[3];
    arg_output = argv[4];
  }
  //------------------Args------------------END

  //------------------Read FASTA------------------
  ifstream input_file;
  string line;
  string reference_string;
  int string_counter = 0;
  input_file.open(arg_reference_path, ios::in);

  while (getline(input_file, line)) {
    if (line[0] == '>') {
      string_counter++;
      if (string_counter <= 1) {
        reference_string = "";
      }
    }
    else {
      if (string_counter <= 1) {
        reference_string += line;
      }
    }
  }
  input_file.close();
  //------------------Read FASTA------------------END

  //------------------Build SA------------------
  reference_string += "$";

  unique_ptr<int64_t[]> suffix_array(new int64_t[reference_string.size()]);
  int64_t n = reference_string.size();
  assert(n > 0);
  int64_t fs = 0;
  int64_t* freq = nullptr;
  
  auto clock_suffix_array_start = chrono::high_resolution_clock::now();

  int64_t ret = libsais64(reinterpret_cast<uint8_t*>(reference_string.data()), suffix_array.get(), n, fs, freq);
  if (ret != 0) {
    cout << "suffix array construction failed; exit code = " << ret << "\n";
  } 
  // else {
  //   cout << "suffix array construction successful!\n";
  //   cout << "[ ";
  //   for (size_t i = 0; i < n; ++i) {
  //     cout << suffix_array[i] << ((i < n-1) ? ", " : " ");
  //   }
  //   cout << "]\n";
  // }
  auto clock_suffix_array_end = chrono::high_resolution_clock::now();
  chrono::duration<double> clock_suffix_array_duration = clock_suffix_array_end - clock_suffix_array_start;
  cout << "Time to build suffix array: " << clock_suffix_array_duration.count() << " s\n";

  // array<int64_t, sizeof(n)> suffix_array_array;
  // for (size_t i = 0; i < n; i++) {
  //   suffix_array_array[i] = suffix_array[i];
  // }
  // cout << suffix_array_array[0];
  //------------------Build SA------------------END

  //------------------Prefix Table------------------
  unordered_map<string, pair<int, int>> prefix_table;
  if (argc == 5) {
    
    string temp_key;
    if (arg_k >= n-1) {
      cout << "Prefix table length is wrong!\n";
      exit(1);
    }

    auto clock_prefix_table_start = chrono::high_resolution_clock::now();
    for (int i = 1; i < n; i++) {
      if (n - suffix_array[i] > arg_k){
        temp_key = reference_string.substr(suffix_array[i], arg_k);
        // cout << temp_key << endl;
        if (prefix_table.count(temp_key) == 0){
          prefix_table[temp_key].first = i;
          prefix_table[temp_key].second = i+1;
        } 
        else {
          prefix_table[temp_key].second = i+1;
        }
      }
    }
    auto clock_prefix_table_end = chrono::high_resolution_clock::now();
    chrono::duration<double> clock_prefix_table_duration = clock_prefix_table_end - clock_prefix_table_start;
    cout << "Time to build prefix table: " << clock_prefix_table_duration.count() << " s\n";

    // print_map(prefix_table);
  }
  //------------------Prefix Table------------------END
  
  //------------------Output------------------
  ofstream output_file;
  output_file.open(arg_output, ios::out | ios::binary);
  cereal::BinaryOutputArchive archive(output_file);
  archive(reference_string);
  archive(prefix_table);
  archive(arg_k);

  // archive(suffix_array);//How to serialize suffix array?????????????????
  // TEMPORARY SOLUTION
  output_file.write((char *) &suffix_array[0], n*sizeof(suffix_array[0]));
  
  output_file.close();
  //------------------Output------------------END


  return 0;
}
