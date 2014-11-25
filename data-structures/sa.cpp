
namespace NS_DC3 {
	/*******************************************************************
	 *
	 * DC3 A(s);
	 * DC3 A(a, n);
	 *
	 * sa - Suffix array
	 * s[A.sa[0]..] < s[A.sa[1]..] < ... < s[A.sa[n - 1]..]
	 *
	 * rank - Suffix rank
	 * A.rank[A.sa[i]] = A.sa[A.rank[i]] = i
	 * s[i..] < s[j..] <=> A.rank[i] < A.rank[j]
	 *
	 * height - Height array
	 * A.height[i] is LCP's length of s[A.sa[i]..] and s[A.sa[i + 1]..]
	 *
	 *******************************************************************/
	struct DC3 {
		int size;
		int *sa, *rank, *height;
		int *block, *tempa, *tempb, *tempc;
		template<typename T>
		DC3(const T *a, int n) {
			Init(a, n);
		}
		DC3(const char *a) {
			Init(a, strlen(a));
		}
		template<typename T>
		DC3(const vector<T> a) {
			Init(a.begin(), a.size());
		}
		template<typename T>
		void Init(const T a, int n) {
			size = n;
			sa = new int[n];
			rank = new int[n];
			height = new int[n];
			block = new int[n + 1];
			tempa = new int[n];
			tempb = new int[n];
			tempc = new int[n + 1];
			int *_a = new int[(n + 2) << 2], *_sa = new int[(n + 2) << 2];

			memset(block, 0, (n + 1) << 2);
			memset(_a + n, 0, ((n + 2) << 4) - (n << 2));

			int minimum = *min_element(a, a + n);
			int maximum = *max_element(a, a + n);
			if (maximum - minimum < n)
				for (int i = 0; i < n; i++)
					_a[i] = a[i] - minimum + 1;
			else {
				copy(a, a + n, tempa);
				sort(tempa, tempa + n);
				int *end = unique(tempa, tempa + n);
				for (int i = 0; i < n; i++)
					_a[i] = upper_bound(tempa, end, a[i]) - tempa + 1;
			}
			SA(_a, _sa, n);
			memcpy(sa, _sa, n << 2);

			for (int i = 0; i < n; i++)
				rank[sa[i]] = i;

			Height(_a, 0, 0);
			for (int i = 1; i < n; i++)
				Height(_a, i, max(height[rank[i - 1]] - 1, 0));

			delete[] _a;
			delete[] _sa;
			delete[] block;
			delete[] tempa;
			delete[] tempb;
			delete[] tempc;
		}
		~DC3() {
			delete[] sa;
			delete[] rank;
			delete[] height;
		}
		void radixsort(int *src, int *dest, int n, int *X) {
			int M = 0;
			for (int i = n; i--; block[X[src[i]]]++)
				M = max(M, X[src[i]]);
			for (int i = 1; i <= M; i++)
				block[i] += block[i - 1];
			for (int i = n; i--; )
				dest[--block[X[src[i]]]] = src[i];
			memset(block, 0, (M + 1) << 2);
		}
		bool cmp(int *a, int i, int j) {
			if (a[i] != a[j])
				return a[i] < a[j];
			else if (j % 3 == 1)
				return tempc[i + 1] < tempc[j + 1];
			else if (a[i + 1] != a[j + 1])
				return a[i + 1] < a[j + 1];
			else
				return tempc[i + 2] < tempc[j + 2];
		}
		void SA(int *a, int *sa, int n) {
			if (n == 1) {
				sa[0] = 0;
				return;
			}
			int *_a = a + n + 2, *_sa = sa + n + 2;
			int _n = 0;
			for (int i = 1; i <= n; i += 3) {
				tempc[i] = _n;
				tempa[_n++] = i;
			}
			for (int i = 2; i < n; i += 3) {
				tempc[i] = _n;
				tempa[_n++] = i;
			}
			radixsort(tempa, tempb, _n, a + 2);
			radixsort(tempb, tempa, _n, a + 1);
			radixsort(tempa, tempb, _n, a);
			_a[tempc[tempb[0]]] = 1;
			for (int i = 1; i < _n; i++)
				_a[tempc[tempb[i]]] = _a[tempc[tempb[i - 1]]] +
					(a[tempb[i]] != a[tempb[i - 1]] ||
					 a[tempb[i] + 1] != a[tempb[i - 1] + 1] ||
					 a[tempb[i] + 2] != a[tempb[i - 1] + 2]);
			SA(_a, _sa, _n);
			_n = 0;
			for (int i = 1; i <= n; i += 3)
				_a[_n++] = i;
			for (int i = 2; i < n; i += 3)
				_a[_n++] = i;
			for (int i = 0; i < _n; i++)
				tempc[_sa[i] = _a[_sa[i]]] = i + 1;
			tempc[n] = 0;
			int _n0 = 0;
			for (int i = 0; i < n; i += 3)
				tempa[_n0++] = i;
			radixsort(tempa, tempb, _n0, tempc + 1);
			radixsort(tempb, tempa, _n0, a);
			for (int i = n % 3 == 1, i0 = 0, s = 0; i < _n || i0 < _n0; )
				sa[s++] = i ==_n || (i0 != _n0 && cmp(a, tempa[i0], _sa[i])) ?
					tempa[i0++] : _sa[i++];
		}
		void Height(int *a, int i, int x) {
			int j = rank[i] + 1;
			if (j != size)
				while (a[i + x] == a[sa[j] + x])
					x++;
			height[rank[i]] = x;
		}
	};
}
un NS_DC3;


