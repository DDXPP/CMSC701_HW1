#include "libsais64.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <cmath>
#include <string>
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
  cout << "./querysa index queries query_mode output\n";
}

void arg_num_warning(int argc) {
  cout << "You have entered " << (argc-1) << " arguments, ";
  cout << "but only 4 arguments are accepted.\n";
  arg_warning();
}

void print_map(std::unordered_map<string, pair<int, int>> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": (" << pair.second.first << ", " << pair.second.second << ")}\n";
    }
}

void print_map2(std::unordered_map<string, string> const &m)
{
    for (auto const &pair: m) {
        std::cout << "{" << pair.first << ": " << pair.second << ")}\n";
    }
}

int lcp (string s1, string s2) {
  int i = 0;
  while (i < min(s1.length(), s2.length())) {
    if (s1[i] != s2[i]) {
      break;
    }
    i += 1;
  }
  return i;
}

int main(int argc, char* argv[]) {
  if (argc != 5) {
    arg_num_warning(argc);
    exit(1);
  }

  string arg_index = argv[1];
  string arg_queries = argv[2];
  string arg_query_mode = argv[3];
  string arg_output = argv[4];

  //------------------Deserialize------------------
  ofstream output_file;
  output_file.open(arg_output, ios::out);

  ifstream input_index_file;
  input_index_file.open(arg_index, ios::in);
  cereal::BinaryInputArchive oarchive(input_index_file);

  string reference_string;
  unordered_map<string, pair<int, int>> prefix_table;
  int64_t arg_k;

  oarchive(reference_string);
  oarchive(prefix_table);
  oarchive(arg_k);

  // cout << reference_string << endl;
  // cout << arg_k << endl;
  // print_map(prefix_table); 
  //----------(temporary solution)
  unique_ptr<int64_t[]> suffix_array(new int64_t[reference_string.size()]);
  int64_t n = reference_string.size();
  assert(n > 0);
  int64_t fs = 0;
  int64_t* freq = nullptr;
  int64_t ret = libsais64(reinterpret_cast<uint8_t*>(reference_string.data()), suffix_array.get(), n, fs, freq);
  input_index_file.close();

  // cout << "[ ";
  // for (size_t i = 0; i < n; ++i) {
  //   cout << suffix_array[i] << ((i < n-1) ? ", " : " ");
  // }
  // cout << "]\n";
  //------------------Deserialize------------------END

  //------------------Read FASTA------------------
  ifstream input_queries_file;
  input_queries_file.open(arg_queries, ios::in);

  unordered_map<string, string> query_map_header_to_sequence;
  string line;
  string id;
  string query_string;
  int query_counter = 0;

  while (getline(input_queries_file, line)) {
    if (line[0] == '>') {
      query_counter++;
      if (query_counter != 1) {
        query_map_header_to_sequence[id] = query_string;
      }
      int first = line.find('>');
      id = line.substr(first, line.find(' ', first) - first); 
      id = id.substr(1); 
      query_string = "";
      query_map_header_to_sequence[id] = query_string;
    }
    else {
      query_string += line;
      query_map_header_to_sequence[id] = query_string;
    }
  }
  input_queries_file.close();
  // print_map2(query_map_header_to_sequence);
  //------------------Read FASTA------------------END

  unordered_map<string, vector<int>> query_map_header_to_hits;
  for (const auto &query_map_header_to_sequence : query_map_header_to_sequence) {
    
    string P = query_map_header_to_sequence.second;
    vector<int> query_hits;

    int m = reference_string.length();
    int l, r, c = 0;
      
    int left_bound = -1;
    int right_bound = -1;
    
    auto clock_query_start = chrono::high_resolution_clock::now();
    
    for (int i = 0; i < 2; i++) {
      int query_sa_index = -1;
      string P_temp = P;
      // P_temp = P_temp.substr(0, P_temp.length()-1);
      l = 0;
      r = m;

      if (i == 0) { // first iteration, left bound
        P_temp.push_back(char((int)'$' - 1));
      }
      else { // second iteration, right bound
        P_temp.push_back(char((int)'z' + 1));
      }

      if (arg_k != 0) { 
        string first_k_elements_in_P = P.substr(0, arg_k);
        if (prefix_table.count(first_k_elements_in_P) != 0) {
          l = prefix_table[first_k_elements_in_P].first - 1;
          r = prefix_table[first_k_elements_in_P].second;
        }
        else {
          if (i == 0)
            cout << "prefix table does not contain any prefixes of the query sequence " << query_map_header_to_sequence.first << "\n";
        }
      }
    
      //------------------Naive------------------
      if (arg_query_mode == "naive") {
        while (l < r) {
          c = floor((r+l)/2);
          string SA_c = reference_string.substr(suffix_array[c]);
          // cout << "l:" << l << ", r:" << r << ", c:" << c << ", SA_c:" << SA_c << ", query_sa_index:" <<query_sa_index << "         ";

          if (strcmp(P_temp.c_str(), SA_c.c_str()) < 0) {
            if (c == l+1) {
              query_sa_index = c;
              break;
            }
            else {
              r = c;
            }
          }

          else if (strcmp(P_temp.c_str(), SA_c.c_str()) > 0) {
            if (c == r-1) {
              query_sa_index = r;
              break;
            }
            else {
              l = c;
            }
          }
        }
      }
      //------------------Naive------------------END

      //------------------Simple Accelerant------------------
      else if (arg_query_mode == "simpaccel") {
        int LCP_P_SA_l = lcp(P_temp, reference_string.substr(suffix_array[l]));
        int LCP_P_SA_r = lcp(P_temp, reference_string.substr(suffix_array[r]));
        int LCP_min_l_r = min(LCP_P_SA_l, LCP_P_SA_r);
      
        while (l < r) {
          c = floor((r+l)/2);
          string SA_c = reference_string.substr(suffix_array[c]);
          int LCP_P_SA_c = lcp(P_temp, reference_string.substr(suffix_array[c]));
      
          // cout << "l:" << l << ", r:" << r << ", c:" << c << ", SA_c:" << SA_c << ", query_sa_index:" <<query_sa_index << "         ";

          if (strcmp(P_temp.substr(LCP_min_l_r).c_str(), SA_c.substr(LCP_min_l_r).c_str()) < 0) {
            if (c == l+1) {
              query_sa_index = c;
              break;
            }
            else {
              r = c;
              LCP_P_SA_l = LCP_P_SA_c;
            }
          }

          else if (strcmp(P_temp.substr(LCP_min_l_r).c_str(), SA_c.substr(LCP_min_l_r).c_str()) > 0) {
            if (c == r-1) {
              query_sa_index = r;
              break;
            }
            else {
              l = c;
              LCP_P_SA_r = LCP_P_SA_c;
            }
          }
        }
      }
      //------------------Simple Accelerant------------------END

      else {
        cout << "please enter either 'naive' or 'simpaccel' for argument query_mode." << endl;
        exit(1);
      }

      if (i == 0) { // first iteration, left bound
        left_bound = query_sa_index;
      }
      else { // second iteration, right bound
        right_bound = query_sa_index;
      }

    }
    auto clock_query_end = chrono::high_resolution_clock::now();
    chrono::duration<double> clock_prefix_table_duration = clock_query_end - clock_query_start;
    cout << "Time to query sequence " << query_map_header_to_sequence.first << ": " << clock_prefix_table_duration.count() << " s\n";
    
    if (left_bound != right_bound && left_bound != -1 && right_bound != -1) {
      for (int i = left_bound; i < right_bound; i++) {
        query_hits.push_back(suffix_array[i]);
      }
    }

    query_map_header_to_hits[query_map_header_to_sequence.first] = query_hits;
    output_file << query_map_header_to_sequence.first << "\t" << query_hits.size(); 
    if (query_hits.size() > 0) { 
      output_file << "\t";
      for (int i = 0; i < query_hits.size(); i++) {
        output_file << query_hits[i] << (i == query_hits.size() - 1 ? "\n" : "\t");
      }
    }
    else {
      output_file << "\n"; 
    }    
  }
  
  output_file.close();
}


  // while (true) {
  //   c = floor((r+l)/2);
  //   bool plt = true;
  //   int i = 0;
  //   while (i < P.length() && suffix_array[c]+i < n) {
  //     if (P[i] < reference_string[suffix_array[c]+i]) {
  //       break;
  //     }
  //     else if (P[i] > reference_string[suffix_array[c]+i]) {
  //       plt = false;
  //       break;
  //     }
  //     i += 1;
  //   }
  //   if (plt) {
  //     if (c == l+1) {
  //       query_sa_index = c;
  //       break;
  //     }
  //     else {
  //       r = c;
  //     }
  //   }
  //   else {
  //     if (c == r-1) {
  //       query_sa_index = r;
  //       break;
  //     }
  //     else {
  //       l = c;
  //     }
  //   }
  // }