#ifndef _DYLIB_BUNDLER_H_
#define _DYLIB_BUNDLER_H_

#include <string>

void initRpaths();

void changeLibPathsOnFile(std::string file_to_fix);

void collectRpaths(const std::string& filename);
void collectRpathsForFilename(const std::string& filename);
std::string searchFilenameInRpaths(const std::string& rpath_dep, const std::string& dependent_file);
std::string searchFilenameInRpaths(const std::string& rpath_file);
void fixRpathsOnFile(const std::string& original_file, const std::string& file_to_fix);

void addDependency(std::string path, std::string dependent_file);
void collectDependencies(const std::string& dependent_file, std::vector<std::string>& lines);
void collectDependencies(const std::string& dependent_file);
void collectSubDependencies();

void doneWithDeps_go();

void createQtConf(std::string directory);
void copyQtPlugins();

#endif
