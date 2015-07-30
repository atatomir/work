var n,lp,cp,op,t,h,i,j,si:longint;
    a,r:array[1..4,1..3]of longint;
    c:char;
    sol:array[1..1005]of longint;

begin
  assign(input,'zar.in'); reset(input);
  assign(output,'zar.out'); rewrite(output);

  readln(n);
  readln(lp,cp);

  for i := 1 to 4 do
    for j := 1 to 3 do
    begin
      r[i,j] := 0;
      a[i,j] := 0;
    end;


  readln(a[1,2],a[3,2],a[2,1],a[2,3],a[2,2],a[4,2]); inc(si); sol[si] := a[1,2];
  readln(op);

  for i := 1 to 4 do
    for j := 1 to 3 do
      r[i,j] := a[i,j];

  for t := 1 to op do
  begin
    read(c);
    case c of
      'u':begin
            h := a[1,2] ; a[1,2] := a[2,2]; a[2,2] := a[3,2]; a[3,2] := a[4,2] ; a[4,2] := h;
            dec(lp);
          end;
      'd':begin
            h := a[4,2] ; a[4,2] := a[3,2] ; a[3,2] := a[2,2] ; a[2,2] := a[1,2]; a[1,2] := h;
            inc(lp);
          end;
      'l':begin
            h := a[2,1]; a[2,1] := a[1,2] ; a[1,2] := a[2,3]; a[2,3] := a[3,2]; a[3,2] := h;
            dec(cp);
          end;
      'r':begin
            h := a[2,1]; a[2,1] := a[3,2]; a[3,2] := a[2,3]; a[2,3] := a[1,2]; a[1,2] := h;
            inc(cp);
          end;
    end;

    if (lp > 0)and(lp < n+1)and(cp > 0)and(cp < n+1) then
    begin
      for i := 1 to 4 do
        for j := 1 to 3 do
          r[i,j] := r[i,j] + a[i,j];
      inc(si); sol[si] := a[1,2];
    end
    else
      break;

  end;

  writeln(r[1,2],' ',r[3,2],' ',r[2,1],' ',r[2,3],' ',r[2,2],' ',r[4,2]);
  for i := 1 to si do write(sol[i],' ');



  close(input);
  close(output);
end.
