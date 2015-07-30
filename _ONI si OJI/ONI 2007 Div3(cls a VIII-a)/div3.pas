const modd = 4001;
var n,k,i,j:longint;
    a:array[1..10]of longint;
    s,r:array[0..2]of longint;

begin
  assign(input,'div3.in'); reset(input);
  assign(output,'div3.out'); rewrite(output);

  readln(n,k);
  for i := 0 to 2 do s[i] := 0;

  for i := 1 to n do
  begin
    read(a[i]); a[i] := a[i] mod 3;
    inc(s[a[i]]);
  end;

  for i := 2 to k do
  begin
    for j := 0 to 2 do r[j] := 0;
    for j := 1 to n do
    begin
      r[a[j]] := (r[a[j]]+s[0])mod modd;
      r[(a[j]+1)mod 3] := (r[(a[j]+1)mod 3]+s[1])mod modd;
      r[(a[j]+2)mod 3] := (r[(a[j]+2)mod 3]+s[2])mod modd;
    end;

    for j := 0 to 2 do
      s[j] := r[j];
  end;

  writeln(s[0]);

  close(input);
  close(output);
end.