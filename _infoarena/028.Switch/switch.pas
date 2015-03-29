var t,i,x,cont:longint;
    par:boolean;


begin
  assign(input,'switch.in'); reset(input);
  assign(output,'switch.out'); rewrite(output);

  readln(t);
  for i := 1 to t do
  begin
    cont := 0;
    read(x); if x = 1 then inc(cont);
    readln(x); if x = 1 then inc(cont);
    read(x); if x = 1 then inc(cont);
    readln(x); if x = 1 then inc(cont);

    if cont mod 2 = 0 then par := true else par := false;
    cont := 0;

    read(x); if x = 1 then inc(cont);
    readln(x); if x = 1 then inc(cont);
    read(x); if x = 1 then inc(cont);
    readln(x); if x = 1 then inc(cont);

    if ((par=true)and(cont mod 2 =0)) or ((par=false)and(cont mod 2 =1)) then writeln('DA') else writeln('NU');
  end;

  close(input);
  close(output);
end.
