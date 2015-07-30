const modd=1000000;
var n,i,sum,h:longint;

begin
  readln(n); sum := 0;
  h := n div 3;
  for i := 0 to h do sum := (sum + (n-3*i)div 2 + 1) mod modd;
  writeln(sum);
end.