
namespace NS_NDC {
	/*********************************************************
	 *
	 * NDC<N, lg(N - 1) + 1> A;
	 *
	 *********************************************************/
	template<int n, int lgn>
	struct NDC {
		int R[lgn][n], r[lgn][n], d[lgn][n];
		bool c[n];
		void Init(vector<int> *E, int root = 0) {
			memset(c, 0, sizeof c);
			memset(d, 0, sizeof d);
			memset(r, 0, sizeof r);
			memset(R, 0, sizeof R);
			// TODO: anything else needed to initialize

			dfs(0, root, E);
		}
		void dfs(int k, int x, vector<int> *E) {
			static int que[n], f[n], s[n], m[n];
			f[x] = que[0] = x;
			int S = 1;
			for (int i = 0; i < S; i++) {
				int u = que[i];
				s[u] = 1;
				m[u] = 0;
				for (int p = E[u].size(); p--; ) {
					int v = E[u][p];
					if (!c[v] && f[u] != v) {
						que[S++] = v;
						f[v] = u;
					}
				}
			}
			int nr = que[S - 1];
			for (int i = S; i--; ) {
				int u = que[i];
				if (i) {
					s[f[u]] += s[u];
					m[f[u]] = max(m[f[u]], s[u]);
				}
				m[u] = max(m[u], S - s[u]);
				if (m[u] < m[nr])
					nr = u;
			}
			c[nr] = 1;
			R[k][nr] = r[k][nr] = nr;
			d[k][nr] = 0;
			// TODO: initialize data structures and update node nr

			for (int p = E[nr].size(); p--; ) {
				int sr = E[nr][p];
				if (!c[sr]) {
					que[0] = sr;
					f[sr] = nr;
					R[k][sr] = nr;
					r[k][sr] = sr;
					d[k][sr] = 1;
					// TODO: update node sr

					int S = 1;
					for (int i = 0; i < S; i++) {
						int u = que[i];
						for (int q = E[u].size(); q--; ) {
							int v = E[u][q];
							if (!c[v] && f[u] != v) {
								que[S++] = v;
								f[v] = u;
								R[k][v] = nr;
								r[k][v] = sr;
								d[k][v] = d[k][u] + 1;
								// TODO: update node v
							}
						}
					}
				}
			}
			for (int p = E[nr].size(); p--; ) {
				int sr = E[nr][p];
				if (!c[sr])
					dfs(k + 1, sr, E);
			}
		}
	};
}
un NS_NDC;


