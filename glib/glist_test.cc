/*
 * Copyright 2017 All Rights Reserved.
 * Author : soygrow
 * Date   : 2017-06-15
 *
 * glist_test.cc
 * ---------------------------------------------------------------------------
 * Test glist function.
 * ---------------------------------------------------------------------------
 */

#include <iostream>
#include <glib.h>

#include "glog/logging.h"

class Person {
 public:
  Person(int id, std::string name, std::string age) : id_(id), name_(name), age_(age) {
    p = new int[10];
    p[0] = 100;
    p[1] = 101;

    LOG(INFO) << " point === " << &(p[0]);
  }
  ~Person() {
    LOG(INFO) << "id_ @@@ " << id_ << " name_ @@@@ " << name_ << " age_ @@@@ " << age_;
    if (p != NULL) {
      delete[] p;
      p = NULL;
    }
  }

  int id_;
  std::string name_;
  std::string age_;
  int* p;
};

Person* person_copy(Person* p) {
  LOG(INFO) << "id_ ==== " << p->id_ << " name_ ==== " << p->name_ << " age_ ==== " << p->age_;
  if (p->p == NULL) {
    LOG(ERROR) << "point is null..................";
  }
  Person* ret = new Person(p->id_, p->name_, p->age_);
  return ret;
};

void destroy_person(Person* p) {
  if (p != NULL && p->p != NULL) {
    LOG(ERROR) << "point destroy ..... " << p->p;
    delete[] p->p;
    p->p = NULL;
  }
  LOG(INFO) << "$$$$$$$$$$$";
}

void TestGlist() {
  LOG(INFO) << "##############################@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
  GSList* head = NULL;
  GSList* newhead = NULL;
  std::string name = "zhanghao";
  std::string age = "26";
  Person* p1 = new Person(1, name, age);
  head = g_slist_append(head, person_copy(p1));
  Person* p2 = new Person(2, "22222", "2222");
  head = g_slist_append(head, person_copy(p2));
  Person* p3 = new Person(3, "33333", "3333");
  head = g_slist_append(head, person_copy(p3));

  LOG(INFO) << "person len ========================== " << g_slist_length(head);
  newhead = g_slist_nth(head, 2);
  LOG(INFO) << "+++++++++ p === " << ((Person*)newhead->data)->p;
  //g_slist_free_full(head, (GDestroyNotify)&destroy_person);
  //LOG(INFO) << "++++++++++";
  //GSList* bak_list = g_slist_copy_deep(newhead, (GCopyFunc)&person_copy, NULL);
  LOG(INFO) << "person len ========================== " << g_slist_length(newhead);
  //newhead = g_slist_copy_deep(newhead, (GCopyFunc)&person_copy, NULL);
  //g_slist_free_full(head, (GDestroyNotify)&destroy_person);    
}

void TestGlistPreAppend() {
  GSList* head = NULL;
  std::string name = "zhanghao";
  std::string age = "26";
  Person* p1 = new Person(1, name, age);
  Person* p2 = new Person(2, "22222", "2222");
  Person* p3 = new Person(3, "33333", "3333");

  LOG(INFO) << "==============================";
  head = g_slist_append(head, person_copy(p1));
  head = g_slist_append(head, person_copy(p2));  
  head = g_slist_append(head, person_copy(p3));

  Person* p4 = new Person(4, "44444", "4444");
  head = g_slist_prepend(head, p4);

  g_slist_free_full(head, (GDestroyNotify)&destroy_person);
}

void TestGlistGetNth() {
  GSList* head = NULL;
  std::string name = "zhanghao";
  std::string age = "26";
  Person* p1 = new Person(1, name, age);
  Person* p2 = new Person(2, "22222", "2222");
  Person* p3 = new Person(3, "33333", "3333");
  Person* p4 = new Person(4, "44444", "4444");
  
  LOG(INFO) << "==============================";
  head = g_slist_append(head, person_copy(p1));
  head = g_slist_append(head, person_copy(p2));  
  head = g_slist_append(head, person_copy(p3));
  head = g_slist_append(head, person_copy(p4));

  LOG(INFO) << "destroy person .......";
  delete p1;
  delete p2;
  delete p3;
  delete p4;
  
  LOG(INFO) << "++++++++++++++++++++++";
  int idx = 1;
  GSList* newhead = g_slist_nth(head, idx);
  for (auto i = 0; i < idx; i ++) {
    Person* p = (Person*)(head->data);
    GSList* headn = head->next;
    destroy_person(p);
  }
  LOG(INFO) << "person len ============== " << g_slist_length(newhead);
}

void TestGlistNoFree() {
  GSList* head = NULL;
  int num[10000];
  for (auto i = 0; i < 10000; i ++) {
    num[i] = i;
    head = g_slist_append(head, GUINT_TO_POINTER(num[i]));
  }

  LOG(INFO) << "==============================";
  LOG(INFO) << "exit ......... after 15s";
  sleep(15);

  g_slist_free(head);
}

void TestGlistNoFree2() {
  LOG(INFO) << "============================== new memory after 10s";
  //sleep(10);
  GSList* head = NULL;
  int* num = new int[10000];
  for (auto i = 0; i < 10000; i ++) {
    num[i] = i;
    head = g_slist_append(head, GUINT_TO_POINTER(num[i]));
  }

  LOG(INFO) << "============================== new ok sleep 10 the delete";
  //sleep(10);
  LOG(INFO) << "============================== delete int";
  delete[] num;
  LOG(INFO) << "============================== delete ok!";

  int p = GPOINTER_TO_INT(head->next->data);
  LOG(INFO) << "p ==== " << p;

  
  LOG(INFO) << "exit ......... after 15s";
  //sleep(15);

  g_slist_free(head);
}

int main(int argc, char** argv) {
  //TestGlist();
  //TestGlistPreAppend();
  //TestGlistGetNth();
  //TestGlistNoFree();

  //sleep(10);
  int i = 0;
  while (i ++ < 1000) {
    TestGlistNoFree2();
  }
  LOG(INFO) << "exit ......... after 100s in main";
  sleep(100);

  return 0;
}
