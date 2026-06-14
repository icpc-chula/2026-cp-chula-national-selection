import sys
input = sys.stdin.readline

n = int(input())
a = input()
b = input()

doing = False
c = 0
for i in range(n):
  if a[i] != b[i]:
    if not doing:
      doing = True
      c += 1
  else:
    doing = False

print(c)