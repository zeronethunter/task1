// Copyright 2022 zenehu

#include <stdio.h>

#include "Subnet.h"

bool make_subnet(Subnet **new_subnet);
void delete (Subnet *subnet);

int main() {
  Subnet *new_subnet = NULL;
  bool is_right = make_subnet(&new_subnet);
  if (is_right) {
    print_subnet(new_subnet);
  } else {
    printf("%s", "Something went wrong!");
  }
  delete (new_subnet);
  return 0;
}

bool make_subnet(Subnet **new_subnet) {
  *new_subnet = (Subnet *)malloc(sizeof(Subnet));
  Subnet *_subnet = *new_subnet;

  _subnet->servers = NULL;
  _subnet->subnet = NULL;
  _subnet->size = 0;

  printf("%s\n", "Input subnet: (x.x.x.0)");

  unsigned int *tmp_ip = NULL;

  tmp_ip = input_ip(stdin, 4);
  if (!tmp_ip) {
    return false;
  }
  if (tmp_ip[3] != 0) {
    return false;
  }
  _subnet->subnet = tmp_ip;

  printf("%s: ", "Your subnet");
  for (int i = 0; i < 3; ++i) {
    printf("%u.", _subnet->subnet[i]);
  }
  printf("%u\n", _subnet->subnet[3]);
  printf("%s", "Input count of servers in this subnet: ");

  _subnet->size = input_int(stdin);
  if (!_subnet->size) {
    return false;
  }
  _subnet->servers = (Server *)malloc(sizeof(Server) * _subnet->size);
  if (!_subnet->servers) {
    return false;
  }

  for (size_t i = 0; i < _subnet->size; ++i) {
    _subnet->servers[i] = (Server){};

    printf("%zu. %s: ", i + 1, "Input dns");
    char *tmp_string = input_string(stdin);
    if (!tmp_string) {
      return false;
    }
    _subnet->servers[i].dns = tmp_string;

    unsigned int *tmp = NULL;

    printf("   %s:\n", "Input ip");
    tmp = input_ip(stdin, 4);
    if (!tmp) {
      return false;
    }
    _subnet->servers[i].ip = tmp;

    printf("   %s:\n", "Input mask");
    tmp = input_ip(stdin, 4);
    if (!tmp) {
      return false;
    }
    _subnet->servers[i].mask = tmp;

    printf("   %s: ", "Input count of threads");
    unsigned int thread_count = input_int(stdin);
    if (!thread_count) {
      return false;
    }
    _subnet->servers[i].thread_count = thread_count;

    printf("   %s: ", "Input count of cores");
    unsigned int core_count = input_int(stdin);
    if (!core_count) {
      return false;
    }
    _subnet->servers[i].core_count = core_count;
  }
  return true;
}

void delete (Subnet *subnet) {
  if (!subnet) {
    return;
  }
  if (subnet->subnet) {
    free(subnet->subnet);
  }
  if (subnet->servers) {
    for (int i = 0; i < subnet->size; ++i) {
      if (subnet->servers[i].ip) {
        free(subnet->servers[i].ip);
      }
      if (subnet->servers[i].dns) {
        free(subnet->servers[i].dns);
      }
      if (subnet->servers[i].mask) {
        free(subnet->servers[i].mask);
      }
    }
    free(subnet->servers);
  }
  free(subnet);
}
