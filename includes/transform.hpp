#pragma once

#include <cstdlib>
#include <string>
#include <vector>

enum TransformType
{
  TRANS_MERGE, TRANS_TRANSLATION
};

struct Params
{
  Params(void) {}
  virtual ~Params(void) = default;

  TransformType transform;
  std::string output;
  bool compute_quality;
};

struct MergeParams : public Params
{
  std::vector<std::string> input;
  bool merge_nodes;
};

struct TranslationParams : public Params
{
  std::string input;
  std::vector<double> coords;
};

// Invalid Params used for error cases
static const struct Params ErrorParams = Params();

class Transform
{
public:
  Transform(void) {}
  ~Transform(void) {}

  // TODO
};
