//uses math;
var n,x,op:longint;
    e,ant,poz,cont:longint;
    p:int64;
    u,anter:longint;


begin
  assign(input,'pesti.in'); reset(input);
  assign(output,'pesti.out'); rewrite(output);

  readln(n,x);

  //op := trunc(log2(n-1));
  p := 1; op := 0;
  while p*1024 <= n-1 do
  begin
    op := op+10;
    p := p*1024;
  end;
  while p*2 <= n-1 do
  begin
    inc(op);
    p := p*2;
  end;

  e := n; ant := 0; poz := x; cont := 0; u := 0; anter := poz;
  while e > 2 do
  begin

    if poz mod 2 =1 then
    begin
      poz := (poz+1)div 2;
      e := (e+1)div 2;
    end
    else
    begin
      poz := poz div 2;
      ant := ant + ((e+1)div 2);
      e := e div 2;
    end;

    inc(u);
    if poz+ant <> anter then cont := u;
    anter := poz+ant;
  end;

  writeln(op,' ',poz+ant,' ',cont);

  close(input);
  close(output);
end.
