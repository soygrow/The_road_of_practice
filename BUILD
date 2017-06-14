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
