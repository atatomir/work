var t,ti,r,p,n,x:longint;
    v:array[1..4]of shortint;
    a,b,c,d,e,f,g:shortint;
    aa,bb,cc,dd,ee,ff,gg:longint;

procedure verif(x:longint);
begin
  if n > x then n := x;
end;

begin
  assign(input,'cifre4.in'); reset(input);
  assign(output,'cifre4.out'); rewrite(output);
  v[1] := 2; v[2] := 3; v[3] := 5; v[4] := 7;

  readln(t);
  for ti := 1 to t do
  begin
    readln(r,p); n := 5000005;
    for a := 1 to 4 do
    begin
      aa := a;
      for b := 1 to 4 do
      begin
        bb := aa*10 + v[b];
        for c := 1 to 4 do
        begin
          cc := bb*10 + v[c];
          for d := 1 to 4 do
          begin
            dd := cc*10 + v[d];
            for e := 1 to 4 do
            begin
              ee := dd*10 + v[e];
              for f := 1 to 4 do
              begin
                ff := ee*10 + v[f];
                for g := 1 to 4 do
                begin
                  gg := ff*10 + v[g];

                  if (gg mod 10) mod p = r then verif(gg mod 10);
                  if (gg mod 100) mod p = r then verif(gg mod 100);
                  if (gg mod 1000) mod p = r then verif(gg mod 1000);
                  if (gg mod 10000) mod p = r then verif(gg mod 10000);
                  if (gg mod 100000) mod p = r then verif(gg mod 100000);
                  if (gg mod 1000000) mod p = r then verif(gg mod 1000000);
                  if gg mod p = r then verif(gg);
                end;
              end;
            end;
          end;
        end;
      end;
    end;
    if n = 5000005 then n := -1;
    writeln(n);
  end;

  close(input);
  close(output);
end.
