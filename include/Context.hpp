#pragma once
#include <unordered_map>
#include <memory>
#include "AST.hpp"
#include <string>
#include <utility>

class ASTNode;

struct Context {
		std::unordered_map<std::string, double> variables;
		std::unordered_map<std::string, std::pair<std::vector<std::string>, std::shared_ptr<ASTNode>>> functions;


		Context makeLocalContext() {
			return { this->variables,this->functions };
		}
};