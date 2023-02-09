#!/usr/bin/env python3
from collections import defaultdict
import bisect
class Solution:
	def countRectangles(self, rectangles, points):
		n=len(points)
		rec=[0]*n
		p=defaultdict(list)
		for i in range(n):
			p[points[i][1]].append((points[i][0],i))
			
		def Lengths(y):
			res=[]
			for m,n in rectangles:
				if n>=y:
					res.append(m)
			return sorted(res)
		
		for y,it in p.items():
			res=Lengths(y)
			for x,ids in it:
				print(x,ids)
				#res[ids]=len(res)-bisect.bisect_left(res,x)
		return res

solve=Solution()
rectangles=[[1,2],[2,3],[2,5]]
points=[[2,1],[1,4]]
print(solve.countRectangles(rectangles, points))