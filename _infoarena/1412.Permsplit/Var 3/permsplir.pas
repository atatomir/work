type interval=record
       l,h:longint;
       hi:longint;
     end;

var n,i,ii,soli,j:longint;
    s:array[0..1000001]of interval;
    bufin,bufout:array[1..65000]of byte;
    x,nnul:interval;
    sol:array[0..1000001]of longint;

function get:interval;
begin
  if ii = 0 then
    get := nnul
  else
    get := s[ii];
end;

procedure addsol(x:longint);
begin
  inc(soli);
  sol[soli] := x;
end;

procedure delete;
begin
  if ii > 0 then dec(ii);
end;

procedure verify;
var y:interval;
    iesi:boolean;
begin
  repeat
    y := get;
    iesi := true;
    if x.h + 1 = y.l then
    begin
      iesi := false;
      x.h  := y.h;
      addsol(y.hi);
      delete;
    end;
    if y.h + 1 = x.l then
    begin
      iesi := false;
      x.l := y.l;
      addsol(y.hi);
      delete;
    end;

  until iesi = true;
  inc(ii);
  s[ii] := x;
end;

begin
  assign(input,'permsplit.in'); reset(input);
  assign(output,'permsplit.out'); rewrite(output);
  settextbuf(input,bufin);
  settextbuf(output,bufout);

  readln(n);
  ii := 1; soli := 0;
  read(s[1].l); s[1].h := s[1].l; s[1].hi := 1;
  nnul.l := -5; nnul.h := -5; nnul.hi := -5;

  for i := 2 to n do
  begin
    read(x.l); x.h := x.l; x.hi := i;
    verify;
  end;

  if ii > 1 then
    writeln(-1)
  else
  begin
    for i := soli downto 1 do write(sol[i],' ');
  end;



  close(input);
  close(output);
end.