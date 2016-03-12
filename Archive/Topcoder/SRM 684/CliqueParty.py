class CliqueParty:
	def maxsize(self, a, k):
		a = list(a)
		n = a.len(a)
		a.sort()
		z = 1
		for l in range(n)
			for r in range(l+1, n)
				last = a[l]
				rlen = a[r]-a[l]
				zz = 2
				for m in range(l+1, r)
					if (a[m]-last)*k >= rlen and (a[r]-a[l])*k >= rlen
						last = a[m]
						zz += 1
				z = max(z, zz)
		return z
