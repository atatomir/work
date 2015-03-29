var n,i:Longint;
    s:array[0..10]of longint;
    ap:array[0..10]of boolean;
    bufout:array[1..65000]of byte;

procedure back(pas:longint);
var i,j:longint;
begin
  if pas = n then
  begin
    for i := 1 to n do write(s[i],' '); writeln();
  end
  else
  begin
    for i := 1 to n do
      if ap[i] = false then
      begin
        ap[i] := true;
        s[pas+1] := i;
        back(pas+1);
        ap[i] := false;
      end;

  end;

end;

begin
  assign(input,'permutari.in'); reset(input);
  assign(output,'permutari.out'); rewrite(output);
  settextbuf(output,bufout);

  readln(n);
  for i := 1 to n do begin s[i] := 0; ap[i] := false; end;

  back(0);

  close(input);
  close(output);
end.