var n,m,i:longint;
    a:array[0..21]of longint;
    facut:boolean;

procedure Divide(s:string;sum,pas:longint);
var str:string;
begin
if not facut then begin
  if pas = m then
  begin
    if sum + a[pas] = n then
    begin
      writeln(s,'+',a[pas]);
      facut := true;
    end;
    if sum - a[pas] = n then
    begin
      writeln(s,'-',a[pas]);
      facut := true;
    end;
  end
  else
  begin
    if pas > 1 then str := s + '+' + char(a[pas]+$30)  else  str := s + char(a[pas]+$30);
    Divide(str,sum+a[pas],pas+1);
    str := s + '-' + char(a[pas]+$30);
    Divide(str,sum-a[pas],pas+1);
  end;
end;
end;

begin
  assign(input,'adunscad.in'); reset(input);
  assign(output,'adunscad.out'); rewrite(output);

  readln(n,m);
  for i := 1 to m do read(a[i]);

  facut := false;
  Divide('',0,1);


  if not facut then writeln('0');

  close(input);
  close(output);
end.
