const zero=ord('0');
      noua=ord('9');
var a,b,c,c1,c2,c3,i,nl,aa,bb,cc,j:longint;
    n,r:array[0..1005]of byte;
    chr:char;
    val:array[1..3]of byte;

procedure aranjeaza;
var t:longint;
begin
  if c1 > c2 then
  begin
    t := c1; c1 := c2; c2 := t;
    t := a; a := b; b := t;
  end;
  if c2 > c3 then
  begin
    t := c2; c2 := c3; c3 := t;
    t := b; b := c; c:= t;
  end;
  if c1 > c2 then
  begin
    t := c1; c1 := c2; c2 := t;
    t := a; a := b; b := t;
  end;
end;

procedure Scrie_tot(start:longint);
var i:longint;
begin
  for i := start to start+aa-1 do r[i] := 1;
  start := start + aa;
  for i := start to start+bb-1 do r[i] := 2;
  start := start + bb;
  for i := start to start+cc-1 do r[i] := 3;
end;

procedure verif_and_modif;
var id:boolean;
    i,j:longint;
begin
  id := true;
  for i := 1 to nl do
    if n[i] <> val[r[i]] then
    begin
      id := false;
      break;
    end;

  if id then
  begin
    i := nl; while (r[i] <> 3)and(i>0) do dec(i);
    j := i-1; while (r[j] <> 2)and(j>0) do dec(j);

    if (i>0) and (j>0) then
    begin
      dec(r[i]); inc(r[j]);
    end
    else
    begin
      i := nl; while (r[i] <> 2)and(i>0) do dec(i);
      j := i-1; while (r[j] <> 1)and(j>0) do dec(j);
      if (i>0) and (j>0) then
      begin
         dec(r[i]); inc(r[j]);
      end
      else
      begin
        i := nl; while (r[i] <> 3)and(i>0) do dec(i);
        j := i-1; while (r[j] <> 1)and(j>0) do dec(j);

        dec(r[i]); inc(r[j])
      end;
    end;

  end;
end;


begin
  assign(input,'tcif.in'); reset(input);
  assign(output,'tcif.out'); rewrite(output);

  readln(a,b,c,c1,c2,c3); nl := 0;
  while not eof(input) do
  begin
    read(chr);
    if (zero <= ord(chr))and(ord(chr)<=noua) then
    begin
      inc(nl);
      n[nl] := ord(chr)-zero;
    end
    else
      break;

  end;

  aranjeaza;

  if a+b+c > nl then
  begin
    if c1 = 0 then begin dec(b); write(c2); end;

    for i := 1 to a do write(c1);
    for i := 1 to b do write(c2);
    for i := 1 to c do write(c3);
  end
  else
  begin
    aa := a; bb := b; cc := c;

    for i := 1 to nl do
    begin
      if aa > 0 then
      begin
        if n[i] <= c1 then
        begin
          r[i] := 1; dec(aa);
          if n[i] < c1 then begin Scrie_tot(i+1); break; end;
          continue;
        end;
      end;

      if bb > 0 then
      begin
        if n[i] <= c2 then
        begin
          r[i] := 2; dec(bb);
          if n[i] < c2 then begin Scrie_tot(i+1); break; end;
          continue;
        end;
      end;

      if cc > 0 then
      begin
        if n[i] <= c3 then
        begin
          r[i] := 3; dec(cc);
          if n[i] < c3 then begin Scrie_tot(i+1); break; end;
          continue;
        end;
      end;

      j := i-1;
      while r[j] = 3 do
      begin
        dec(j);
        inc(cc);
      end;

      case r[j] of
        1: begin inc(aa); dec(bb); end;
        2: begin inc(bb); dec(cc); end;
      end;
      inc(r[j]);  Scrie_tot(j+1); break;

    end;

    val[1] := c1; val[2] := c2; val[3] := c3;

    verif_and_modif;

    for i := 1 to nl do write(val[r[i]]);

  end;



  close(input);
  close(output);
end.
