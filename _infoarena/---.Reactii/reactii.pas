type solutie=record
       l,h:smallint;
     end;
var n,m,t,i,ii:longint;
    s:array[0..15001]of solutie;
    bufin:array[1..65000]of byte;
    x,nnul:solutie;

procedure push(x:solutie);
begin
  inc(ii);
  s[ii].l := x.l;
  s[ii].h := x.h;
end;

function get:solutie;
begin
  if ii > 0 then
    get := s[ii]
  else
    get := nnul;
end;

procedure delete;
begin
  if ii > 0 then dec(ii);
end;

procedure verify;
var y:solutie;
    iesi:boolean;
begin
  repeat
    iesi := true;
    y := get;
    if y.l = x.h+1 then
    begin
      iesi := false;
      x.h := y.h;
      delete;
    end;
    if y.h = x.l-1 then
    begin
      iesi := false;
      x.l := y.l;
      delete;
    end;
  until iesi=true;
end;


begin
  assign(input,'reactii.in'); reset(input);
  assign(output,'reactii.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  readln(m);
  nnul.l := -5; nnul.h := -5;

  for t := 1 to m do
  begin
    read(s[1].l);
    s[1].h := s[1].l; ii := 1;
    for i := 2 to n do
    begin
      read(x.l); x.h := x.l;
      verify;
      push(x);
    end; readln();

    if ii = 1 then writeln(1) else writeln(0);

  end;

  close(input);
  close(output);
end.