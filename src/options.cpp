#include "options.hpp"

#include <memory>

OptionsParser::OptionsParser(const std::string& file_name)
  : m_file_name(file_name)
{
  m_data = cpptoml::parse_file(m_file_name);
}

Params *OptionsParser::parse(void)
{
  auto transform = m_data->get_table("transform");
  auto name = *transform->get_as<std::string>("name");

  /* Merge case */
  if (name.compare("merge") == 0) {
    struct MergeParams *params = new MergeParams();
    params->merge_nodes = *transform->get_as<bool>("merge_nodes");
    
    auto io = m_data->get_table("io");
    params->input = *io->get_array_of<std::string>("inputs");
    params->output = *io->get_as<std::string>("output");

    auto quality = m_data->get_table("quality");
    params->compute_quality = *quality->get_as<bool>("compute_quality");

    return params;

  /* Transform case */
  } else if (name.compare("translate") == 0) {
    //FIXME: Seems like TranslationParams doesn't parse very well
    struct TranslationParams *params = new TranslationParams();
    params->coords = *transform->get_array_of<double>("translation");

    auto io = m_data->get_table("io");
    params->input = *io->get_as<std::string>("input");
    params->output = *io->get_as<std::string>("output");

    auto quality = m_data->get_table("quality");
    params->compute_quality = *quality->get_as<bool>("compute_quality");

    return params;

  /* Error case */
  } else {
    //TODO: throw error
  }

  return nullptr;
}
