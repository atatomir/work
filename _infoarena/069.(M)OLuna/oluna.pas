var t,ti:longint;
    n,h,st,en,p,s2,e2,pos:int64;
    v:int64;

function calc(pos:int64):int64;
begin
  if pos <= 0 then begin calc := 0; exit; end;

  if pos mod 3 = 0 then
  begin
    h := pos div 3;
    calc := 3*((h*(h+1))div 2);
  end
  else
  begin
    h := pos div 3;
    calc := 3*((h*(h+1))div 2) + (h+1)*(pos mod 3);
  end;
end;

begin
  assign(input,'oluna.in'); reset(input);
  assign(output,'oluna.out'); rewrite(output);

  readln(t);
  for ti := 1 to t do
  begin
    readln(n);
    if n mod 2 = 0 then
    begin
      if n <= 4 then
        v := 0
      else
      begin
        en := n div 2 - 3;
        st := en mod 3;
        e2 := en div 2 + 1;
        {s2 := st div 2 + 1;}s2 := 1;
        v := ((s2+e2)*(e2-s2+1)) div 2;

        pos := en-3;
        while ((pos+3)div 2 - 1 = pos div 2)and(pos >= 0) do pos := pos -3;
        pos := (pos+3)div 2 ;


        v := v - calc(pos);

      end;


      writeln(v);
    end
    else
      writeln(0);

  end;



  close(input);
  close(output);
end.