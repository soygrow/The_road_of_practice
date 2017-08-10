# The BUILD rules.

package(default_visibility = ["//visibility:public"])

cc_binary(
  name = "regex",
  srcs = ["regex/regex_test.cc"],
  linkopts = [
     "-lboost_regex"
  ],
)

cc_binary(
  name = "tokenizer",
  srcs = ["tokenizer/tokenizer.cc"],

)

cc_binary(
  name = "format",
  srcs = ["format/format.cc"],
)

cc_binary(
  name = "thread",
  srcs = ["thread/thread.cc"],
  linkopts = [
              "-lboost_thread -lboost_system",
             ],
)

cc_binary(
  name = "thread_condition",
  srcs = ["thread/thread_condition.cc"],
  linkopts = [
              "-lboost_thread -lboost_system",
             ],
)

cc_binary(
  name = "thread_tls",
  srcs = ["thread/thread_TLS.cc"],
  linkopts = [
              "-lboost_thread -lboost_system",
             ],
)

cc_binary(
  name = "intelligent_pointer",
  srcs = ["intelligent_pointer/intelligent_point.cc"],
)

cc_binary(
  name = "glist",
  srcs = ["glib/glist_test.cc"],
  deps = [
          "//third_party/glog",
         ],
  copts = [
           "-I/usr/include/glib-2.0",
           "-I/usr/lib/x86_64-linux-gnu/glib-2.0/include",
          ],
  linkopts = [
              "-lgobject-2.0 -lglib-2.0"
             ],
)

cc_binary(
  name = "time_chrono",
  srcs = ["time_chrono/time.cc"],
  deps = [
          "//third_party/glog",
          "//third_party/gflags",
         ],
)

cc_binary(
  name = "asio",
  srcs = ["asio/asio_timer.cc"],
  deps = [
          "//third_party/glog",
          "//third_party/gflags",
         ],
  linkopts = [
              "-lboost_thread -lboost_system",
             ],
)

cc_binary(
  name = "asio_socket",
  srcs = ["asio/asio_socket.cc"],
  deps = [
          "//third_party/glog",
          "//third_party/gflags",
         ],
  linkopts = [
              "-lboost_thread -lboost_system",
             ],
)

cc_binary(
  name = "backtrack",
  srcs = ["backtrack/backtrack.cc"],
  copts = [
           "-I/usr/local/include",
           "-L/usr/local/lib",
         ],
  linkopts = [
              "-lunwind",
             ],
)

cc_binary(
  name = "backtrace_thread",
  srcs = ["backtrack/backtrace_thread.cc"],
  copts = [
           "-I/usr/local/include",
           "-L/usr/local/lib",
         ],
  linkopts = [
              "-lunwind -lboost_thread -lboost_system",
             ],
)

cc_binary(
  name = "crash",
  srcs = ["crash.cc"],
)

cc_binary(
  name = "test_const_string",
  srcs = ["test_string/test_const_string.cc"],
)

cc_binary(
  name = "epoll",
  srcs = ["linux-api/epoll.cc"],
  deps = [
    "//third_party/glog",
    "//third_party/gflags",
  ],

)

# Unix-pro
cc_binary(
  name = "thread_create",
  srcs = ["UnixPro/thread_create.cc"],
  deps = [
          "//third_party/glog",
          "//third_party/gflags",
         ],
)

cc_binary(
  name = "thread_exit",
  srcs = ["UnixPro/thread_exit.cc"],
  deps = [
          "//third_party/glog",
          "//third_party/gflags",
         ],
)

cc_binary(
  name = "daemon",
  srcs = ["UnixPro/daemon.cc"],
  deps = [
          "//third_party/glog",
          "//third_party/gflags",
         ],
)


# leetcode
cc_binary(
  name = "evaluate-reverse-polish-notation",
  srcs = ["leetcode/evaluate-reverse-polish-notation.cc"],
  deps = [
          "//third_party/glog",
          "//third_party/gflags",
         ],
)

cc_binary(
  name = "max-points-on-a-line",
  srcs = ["leetcode/max-points-on-a-line.cc"],
  deps = [
          "//third_party/glog",
          "//third_party/gflags",
         ],
)

cc_binary(
  name = "sort_list",
  srcs = ["leetcode/sort_list.cc"],
  deps = [
          "//third_party/glog",
          "//third_party/gflags",
         ],
  linkopts = [
              "-lpthread",
             ],
)

