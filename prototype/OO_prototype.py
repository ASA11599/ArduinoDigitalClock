class Time:

	def __init__(self,h,m,s):
		self.h = h
		self.m = m
		self.s = s
	
	def __str__(self):
		return str(self.h) + ":" + str(self.m) + ":" + str(self.s)
	
	def main(self):
		self.s += 1
		if self.s == 60:
			self.s = 0
			self.m += 1
		if self.m == 60:
			self.m = 0
			self.h += 1
		if self.h == 24:
			self.h = 0


class Date:

	num_of_days_in_each_months = {1:31,2:28,3:31,4:30,5:31,6:30,7:31,8:31,9:30,10:31,11:30,12:31}

	def __init__(self,d,m,y):
		self.d = d
		self.m = m
		self.y = y
	
	def __str__(self):
		return str(self.d) + "|" + str(self.m) + "|" + str(self.y)

	def is_leap_year(self):
		'''
		Date -> bool

		returns True if the current year is a leap year
		'''
		if ((self.y % 4 == 0) and (self.y % 100 != 0)) or (self.y % 400 == 0):
			return True
		return False

	def main(self):
		self.d += 1
		if self.is_leap_year() and self.m == 2:
			if self.d == 30:
				self.d = 0
		elif self.d == (Date.num_of_days_in_each_months[self.m]) + 1:
			self.d = 0
			self.m += 1
		if self.m == 12:
			self.m = 0
			self.y += 1


class Stopwatch:

	def __init__(self):
		self.s = 0
		self.m = 0
		self.stopped = False

	def __str__(self):
		return str(self.m) + ":" + str(self.s)

	def stop(self):
		self.stopped = True

	def reset(self):
		self.s = 0
		self.m = 0

	def main(self):
		if not self.stopped:
			self.s += 1
			if self.s == 60:
				self.s = 0
				self.m += 1


class Timer:

	def __init__(self,m,s):
		self.m = m
		self.s = s
	
	def __str__(self):
		return str(self.m) + ":" + str(self.s)
	
	def main(self):
		if self.s != 0 and self.m != 0:
			self.s = self.s - 1
			if self.s == 0:
				self.s = 59
				self.m = self.m - 1