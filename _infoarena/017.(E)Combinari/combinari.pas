var n,k,i:longint;
    a:array[0..20]of longint;
    bufout:array[1..65000]of byte;

procedure Rezolva(pos,ku:longint);
var i,j:longint;
begin
  for i := pos to (n-k+ku) do
  begin
    a[ku] := i;
    if ku = k then
    begin
      for j := 1 to k do write(a[j],' '); writeln();
    end
    else
      Rezolva(i+1,ku+1)
  end;
end;

begin
  assign(input,'combinari.in'); reset(input);
  assign(output,'combinari.out'); rewrite(output);
  settextbuf(output,bufout);

  readln(n,k);
  Rezolva(1,1);


  close(input);
  close(output);
end.
