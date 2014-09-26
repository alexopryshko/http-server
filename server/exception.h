class bad_request : public std::exception {
public:
    bad_request() {};
    ~bad_request() throw() {};
};

class forbidden : public std::exception {
public:
    forbidden() {};
    ~forbidden() throw() {};
};

class not_found : public std::exception {
public:
    not_found() {};
    ~not_found() throw() {};
};

class method_not_allowed : public std::exception {
public:
    method_not_allowed() {};
    ~method_not_allowed() throw() {};
};

