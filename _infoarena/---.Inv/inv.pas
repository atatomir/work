const modd=9917;
var n,i,l,x:longint;
    sum:longint;
    st,a:array[0..100000]of longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'inv.in'); reset(input);
  assign(output,'inv.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n); l := 0; sum := 0; st[0] := -11;

  for i := 1 to n do read(a[i]);

  for i := n downto 1 do
  begin
    x := a[i];
    while (l > 0)and(st[l] < x) do dec(l);
    inc(l); st[l] := x;

    sum := (sum + (n-i - l+1) mod modd)mod modd;

  end;

  writeln(sum);


  close(input);
  close(output);
end.
