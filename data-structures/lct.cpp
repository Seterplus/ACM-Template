
namespace NS_LCT {
	/*********************************************************
	 *
	 * LCT A(n);
	 *
	 * Do / Done - Get path information from node x to node y
	 * Ex.:
	 * LCT::S *t = A.Do(x, y);
	 * printf("%d\n", t->ans); // get value
	 * t->a = a; // place a mark
	 * A.Done(t);
	 *
	 * Cut / Link - Dynamic operation
	 * Ex.:
	 * A.Cut(x, y);
	 * A.Link(x, y);
	 *
	 *********************************************************/
	struct LCT {
		struct S {
			S *c[2], *f;
			bool r;
		} null, *pool, *t;

		void InitTree(vector<int> E[], int r) {
			//TODO: initialize tree with edge set E and root r
			node(&null, &null, 0);
			deque<int> Q;
			Q.pb(r);
			node(pool + r, &null, 1);
			while (!Q.empty()) {
				int x = Q.front();
				Q.pf();
				for (unsigned i = 0; i < E[x].size(); i++) {
					int r = E[x][i];
					if (!pool[r].f) {
						Q.pb(r);
						node(pool + r, pool + x, 1);
					}
				}
			}
		}

		S *node(S *x, S *f, int v) {
			x->f = f;
			x->c[0] = x->c[1] = &null;
			x->r = 0;
			//TODO: initialize node x with value v

			return x;
		}
		S *push(S *x) {
			if (x == &null)
				return x;
			if (x->r) {
				x->r = 0;
				x->c[0]->r ^= 1;
				x->c[1]->r ^= 1;
				swap(x->c[0], x->c[1]);
			}
			//TODO: push the mark down to its children

			return x;
		}
		S *updt(S *x) {
			if (x == &null)
				return x;
			push(x->c[0]);
			push(x->c[1]);
			//TODO: update node x with its unmarked children

			return x;
		}

		LCT(int n) {
			pool = new S[n];
			memset(pool, 0, n * (sizeof(S)));
		}
		~LCT() {
			delete[] pool;
		}
		S *fa(S *x) {
			return (x->f->c[0] == x || x->f->c[1] == x) ? x->f : &null;
		}
		S *rot(S *x) {
			S *fx = fa(x), *ffx = push(fa(fx));
			bool c = push(fx)->c[1] == push(x), fc = ffx->c[1] == fx;
			if (fx != &null) {
				x->f = fx->f;
				if ((fx->c[c] = x->c[!c]) != &null)
					fx->c[c]->f = fx;
				if (ffx != &null)
					ffx->c[fc] = x;
				fx->f = x;
				updt(x->c[!c] = fx);
			}
			return x;
		}
		S *splay(S *x, S *p) {
			if (x == &null)
				return x;
			S *fx, *ffx;
			for (; (fx = fa(x)) != p; rot(x))
				if ((ffx = fa(fx)) != p)
					rot((ffx->c[1] == fx) ^ (fx->c[1] == x) ? x : fx);
			return updt(push(x));
		}
		S *Access(S *x) {
			S *t = &null;
			do {
				splay(x, &null)->c[1] = t;
				t = updt(x);
				x = t->f;
			} while (x != &null);
			return splay(t, &null);
		}
		S *LCA(S *x, S *y) {
			Access(x);
			return Access(y);
		}
		S *LCA(int x, int y) {
			return LCA(pool + x, pool + y);
		}
		bool Same(S *x, S *y) {
			Access(x);
			return Access(y) == x || splay(x, &null)->f != &null;
		}
		bool Same(int x, int y) {
			return Same(pool + x, pool + y);
		}
		bool Cut(S *x, S *y) {
			if (!Same(x, y))
				return 0;
			Access(x);
			if (Access(y) == x) {
				Access(x);
				splay(y, &null)->f = &null;
			} else
				splay(x, &null)->f = &null;
			return 1;
		}
		bool Cut(int x, int y) {
			return Cut(pool + x, pool + y);
		}
		bool Link(S *x, S *y) {
			if (Same(x, y))
				return 0;
			x->r = 1;
			x->f = y;
			return 1;
		}
		bool Link(int x, int y) {
			return Link(pool + x, pool + y);
		}
		S *Do(S *x, S *y) {
			if (!Same(x, y))
				return &null;
			Access(x);
			S *r = splay(Access(y), &null);
			t = r->c[0];
			r->c[0] = x == r ? &null : splay(x, &null);
			r->c[0]->r ^= 1;
			return updt(r);
		}
		S *Do(int x, int y) {
			return Do(pool + x, pool + y);
		}
		void Done(S *x) {
			if (x != &null) {
				push(x)->c[0]->r ^= 1;
				x->c[0] = t;
				updt(x);
			}
		}
	};
}
un NS_LCT;


