var n,i:longint;
    a:array[0..20]of longint;
    bufout:array[1..65000]of byte;

procedure Rezolva(pos,sel:longint);
begin
  if pos < n then Rezolva(pos+1,sel);
  a[sel+1] := pos;
  for i := 1 to sel+1 do write(a[i],' '); writeln();
  if pos < n then Rezolva(pos+1,sel+1);
end;

begin
  assign(input,'submultimi.in'); reset(input);
  assign(output,'submultimi.out'); rewrite(output);
  settextbuf(output,bufout);

  readln(n);
  Rezolva(1,0);

  close(input);
  close(output);
end.