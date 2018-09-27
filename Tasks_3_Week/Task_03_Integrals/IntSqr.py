def main():
 def integral_square():
  def function(x):
   return x * x
  with open("input.txt") as file:
   lines = file.read().strip() 
  a=lines[0]
  b=lines[1]
  n=lines[2]
  h=(b-a)/n
  for i in range (1,n):
   s += function(a + i * h)
  return ((function(a)+function(b)+2*s)* h/2)
 with open('output.txt', 'a') as answer:
  answer.write(integral_square())

if __name__ == "__main__":
 main()