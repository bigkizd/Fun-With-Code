#include <bits/stdc++.h>
using namespace std;

#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)
#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
#define fi first
#define se second
#define pb push_back
#define pf push_front
#define mp make_pair
#define inf 1000000005
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define MOD 1000000007
#define SZ(a) ((ll)(a).size())

typedef long long ll;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define eps 1e-12
typedef pair<int, int> II;
typedef pair<ll, ll> LL;
template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcnt(s); }
template<class T> T gcd(T a, T b) { T r; while (b != 0) { r = a % b; a = b; b = r; } return a; }
template<class T> T lcm(T a, T b) { return a / gcd(a, b) * b; }
/* Author: Toan Dao Minh */
/** END OF TEMPLATE **/


int32_t main() {
	int JUDGE_ONLINE = 1;
	if (fopen("in.txt", "r")) {
		JUDGE_ONLINE = 0;
		assert(freopen("in.txt", "r", stdin));
		//assert(freopen("out.txt", "w", stdout));
	}
	else {
		ios::sync_with_stdio(0);
		cin.tie(0);
		cout << (fixed) << setprecision(9) << boolalpha;
	}
	

	return 0;
}
