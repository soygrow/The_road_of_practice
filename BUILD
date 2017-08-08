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
  name = "thread_create",
  srcs = ["UnixPro/thread_create.cc"],
  deps = [
          "//third_party/glog",
          "//third_party/gflags",
         ],
  linkopts = [
             ],
)
