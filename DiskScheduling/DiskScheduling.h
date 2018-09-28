enum Algorithm
{
	NONE = -1, FCFS = 0, SSTF , SCAN , CSCAN 
};

struct Request
{
	int* Request;
	bool* Serviced;
	int Number_of_Req;
};

struct IntPair
{
	int p1;
	int p2;
};

class Disk
{
private:
	Algorithm m_Algo;
	Request m_Req;
	int m_Low;
	int m_High;
	int m_Position;
public:
	Disk(int low, int high);
	~Disk();

	void RunAlgoritm();

	void SetAlgorithm(int a);
	void SetRequest(int n, int* r);
	void SetPosition(int p);

	Algorithm GetAlgorithm() { return m_Algo; }
	Request GetRequest() { return m_Req; }
	int GetPosition() { return m_Position; }
	IntPair GetLimits() { return {m_Low, m_High}; }
};
