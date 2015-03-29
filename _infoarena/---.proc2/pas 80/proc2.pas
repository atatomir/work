type hnod=record
       id,t:longint;
     end;
var n,m,i,cf,ct,t,d,s,proc:longint;
    hf:array[-1..1000005]of longint;    //procesoare libere
    ht:array[-1..100005]of hnod;        //task-uri in desfasurare

function c1(x:longint):longint; begin c1 := 2*x; end;
function c2(x:longint):longint; begin c2 := 2*x+1; end;
function p(x:longint):longint; begin p := x div 2; end;

procedure hf_up(nod:longint);inline;
var par,t:longint;
begin
  repeat
    par := p(nod);
    if hf[par] > hf[nod] then
    begin
      t := hf[par]; hf[par] := hf[nod]; hf[nod] := t;
      nod := par;
    end
    else
      exit;
  until 1 = 0;
end;

procedure hf_down(nod:longint);inline;
var ch1,ch2,t:longint;
begin
  repeat
    ch1 := c1(nod);
    ch2 := c2(nod);
    if ch1 > cf then ch1 := -1;
    if ch2 > cf then ch2 := -1;
    if hf[ch1] > hf[ch2] then ch1 := ch2;
    if hf[nod] > hf[ch1] then
    begin
      t := hf[nod]; hf[nod] := hf[ch1]; hf[ch1] := t;
      nod := ch1;
    end
    else
      exit;
  until 1 = 0;
end;

procedure ht_up(nod:longint);inline;
var par:longint;
    t:hnod;
begin
  repeat
    par := p(nod);
    if ht[par].t > ht[nod].t then
    begin
      t := ht[par]; ht[par] := ht[nod]; ht[nod] := t;
      nod := par;
    end
    else
      exit;
  until 1 = 0;
end;

procedure ht_down(nod:longint);inline;
var ch1,ch2:longint;
    t:hnod;
begin
  repeat
    ch1 := c1(nod);
    ch2 := c2(nod);
    if ch1 > ct then ch1 := -1;
    if ch2 > ct then ch2 := -1;
    if ht[ch1].t > ht[ch2].t then ch1 := ch2;
    if ht[nod].t > ht[ch1].t then
    begin
      t := ht[nod]; ht[nod] := ht[ch1]; ht[ch1] := t;
      nod := ch1;
    end
    else
      exit;
  until 1 = 0;
end;

procedure hf_del();inline;
begin
  hf[1] := hf[cf];
  dec(cf);
  if cf >= 1 then hf_down(1);
end;

procedure hf_add(x:longint);inline;
begin
  inc(cf);
  hf[cf] := x; hf_up(cf);
end;

procedure ht_del();inline;
begin
  ht[1] := ht[ct];
  dec(ct);
  if ct >= 1 then ht_down(1);
end;

procedure ht_add(t,id:longint);inline;
begin
  inc(ct);
  ht[ct].t := t; ht[ct].id := id; ht_up(ct);
end;

begin
  assign(input,'proc2.in'); reset(input);
  assign(output,'proc2.out'); rewrite(output);

  readln(n,m);
  hf[0] := 0; ht[0].t := 0;
  hf[-1] := 1 shl 31-3 ; ht[-1].t := hf[-1];

  for i := 1 to n do hf[i] := i;
  cf := n ; ct := 0;

  for t := 1 to m do
  begin
    readln(d,s); s := d+s;

    while ct <> 0 do
    begin
      if ht[1].t > d then break;
      hf_add(ht[1].id);
      ht_del();
    end;

    proc := hf[1];
    hf_del();
    writeln(proc);
    ht_add(s,proc);
  end;



  close(input);
  close(output);
end.