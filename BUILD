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

