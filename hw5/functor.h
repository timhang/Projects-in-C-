#include<string>
struct AlphaStrComp {
    bool operator()(const std::string& lhs, const std::string& rhs);
    
  };

  struct LengthStrComp {
    bool operator()(const std::string& lhs, const std::string& rhs);
    
  };

  struct NumStrComp {
    bool operator()(const std::string& lhs, const std::string& rhs);
  };

