#include <utility>
#include <nudny/cmd/cli_parser.hpp>

namespace nudny::cmd {

	CliParser::CliParser(int t_argc, char* t_argv[]) {
		parse(t_argc, t_argv);
	}
	
	void CliParser::parse(int t_argc, char* t_argv[]) {
		for(int i=1; i<t_argc; i++) {
			std::string arg = t_argv[i];
			if(arg.rfind("--")==0 && i + 1 < t_argc) {
				std::string key = arg.substr(2);
				std::string val = t_argv[++i];
				m_data[key] = val;
			} else {
				m_data["positional"].push_back(t_argv[i]);
			}
		}
	}
	
	std::string CliParser::get(const std::string& t_key) const {
		if(m_data.contains(t_key)) {
			return m_data[t_key];
		}
		throw std::invalid_argument("Unrecognized param " + t_key + "!");
	}

	std::string CliParser::get(unsigned int t_index) const {
		if(m_data["positional"].size() > t_index) {
			return m_data["positional"][t_index];
		}
		throw std::invalid_argument("CLI provided less than " + std::to_string(t_index) 
				+ " parameters (" + std::to_string(m_data["positional"].size()) + ").");
	}

	const nlohmann::json& CliParser::getJson() const { 
		return m_data;
	}

	const nlohmann::json& CliParser::get(void) const {
		return getJson();
	}

	bool CliParser::exist(const std::string& key) const {
		return m_data.contains(key);
	}

	bool CliParser::exist(unsigned int idx) const {
		return m_data["positional"].size() < idx;
	}

	std::string CliParser::operator()(const std::string& t_key) const {
		return get(t_key);
	}

	std::string CliParser::operator()(unsigned int t_index) const {
		return get(t_index);
	}

	void Commander::setCli(const std::shared_ptr<CliParser>& t_cli) {
		m_cli = t_cli;
	}

	void Commander::setCli(const CliParser& t_cli) {
		m_cli = std::make_shared<CliParser>(t_cli);
	}

	void Commander::check() const {
		if(!m_cli)
			throw std::runtime_error("CLI parser not set!");
	}	

	const std::shared_ptr<CliParser>& Commander::cli(void) const {
		check();
		return m_cli;
	}

	std::string Commander::cli(const std::string& t_key) const {
		check();
		return (*m_cli)(t_key);
	}

	std::string Commander::cli(unsigned int t_i) const {
		check();
		return (*m_cli)(t_i);
	}
}; // namespace nd::cmd
