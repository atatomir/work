const modd=64997;
var a:array[0..2805,1..2]of longint;
    n,k,i,j,s,d,h,t:longint;

begin
  assign(input,'robot.in'); reset(input);
  assign(output,'robot.out'); rewrite(output);

  readln(n,k);

  s := 1; d := 2;
  for i := 0 to k do a[i,s] := 0;

  a[0,d] := 0;

  for j := k to n do
  begin
    a[1,d] := 1; h := j-1;
    for i := 2 to h do
    begin
      a[i,d] := a[i,s] + a[i-1,d];
      a[i,d] := a[i,d] mod modd;
    end;

    t := s; s := d; d := t;

  end;

  writeln(a[n-1,s]);



  close(input);
  close(output);
end.