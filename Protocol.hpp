class Protocol {
	public:
		Protocol () {};
		virtual int * receive() = 0;
		virtual void send(int * data) = 0;
		
	protected:
		int port;
};