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
  for i in range (n):
   s += function(a + i * h)
  return (s * h)
 with open('output.txt', 'a') as answer:
  answer.write(integral_square())

if __name__ == "__main__":
 main()