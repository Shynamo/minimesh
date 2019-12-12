#pragma once

#include <cstdlib>
#include <string>
#include <vector>
#include <vtkSmartPointer.h>
#include <vtkDataSet.h>

enum TransformType
{
  TRANS_MERGE, TRANS_TRANSLATION
};

/* ======= PARAMS ======= */

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

/* ======= TRANSFORM ======= */

class Transform
{
public:
  Transform(void) : _dataset(nullptr) {}
  virtual ~Transform(void) {}

  virtual vtkSmartPointer<vtkDataSet> start(void) = 0;
  void setParams(Params *params);
  bool saveOutput(void); /// Return true if success, false if failure
  bool getOutput(void);
  void computeQuality(void);

protected: 
  Params *_params; /// Transformation parameters
  vtkSmartPointer<vtkDataSet> _dataset; /// Transformed dataset
};


class MergeTransform : public Transform
{
public:
  MergeTransform(Params *params);
  virtual ~MergeTransform(void) {}

  virtual vtkSmartPointer<vtkDataSet> start(void);

protected: 
  MergeParams *_params;
};

class TranslationTransform : public Transform
{
public:
  TranslationTransform(Params *params);
  virtual ~TranslationTransform(void) {}

  virtual vtkSmartPointer<vtkDataSet> start(void);

protected: 
  TranslationParams *_params;
};
