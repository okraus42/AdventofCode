#!/usr/bin/python3

FILE_NAME = 'input.txt'

# Open the file and read its content (using strip to remove extraneous whitespace)
with open(FILE_NAME, 'r') as file:
    s = file.read().strip()

N = len(s)
# dp[i] will store the decompressed length of s[i:]
dp = [0] * (N + 1)
dp[N] = 0  # Base: an empty string has length 0

# Process the string from rightmost character to the beginning.
for i in range(N - 1, -1, -1):
	if s[i] != '(':
		# Normal character: count 1 plus whatever follows.
		dp[i] = 1 + dp[i + 1]
	else:
		# We have encountered a marker starting at position i.
		# Find the corresponding closing parenthesis.
		j = s.find(')', i)
		if j == -1:
			raise ValueError("Malformed marker: no closing ')' found")
		
		# Extract the marker "AxB" (without the parentheses)
		marker = s[i + 1:j]
		try:
			num_chars, repeat = map(int, marker.split('x'))
		except ValueError:
			raise ValueError("Malformed marker: expected two integers separated by 'x'")
		
		# The repeated segment is the next num_chars characters, starting at index j+1.
		# Since dp[j+1] is the decompressed length of s[j+1:],
		# and dp[j+1+num_chars] is the decompressed length of s[j+1+num_chars:],
		# the decompressed length of the segment s[j+1:j+1+num_chars] is:
		L_segment = dp[j + 1] - dp[min(j + 1 + num_chars, N)]
		
		# The decompressed length starting at i is:
		#   (the repeated segment expanded) + (the remainder of the string after the segment)
		dp[i] = repeat * L_segment + dp[min(j + 1 + num_chars, N)]

# The final decompressed length is dp[0]
result = dp[0]
print(result)