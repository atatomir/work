var n,m,i,h,rpos1,rpos2,jpos1,jpos2:longint;
    r,j:array[1..101,1..101]of longint;
    bufin:array[1..65000]of byte;
    x:char;
    min,pos1m,pos2m,mint:longint;

procedure parcurge_r(x,y:integer);
begin
  //writeln(x,' !',y);
  if (x > 1) and  (r[x-1,y]<>-1) and (r[x-1,y] > r[x,y]+1) then begin  r[x-1,y] := r[x,y]+1; parcurge_r(x-1,y);   end;
  if (x < n) and  (r[x+1,y]<>-1) and (r[x+1,y] > r[x,y]+1) then begin  r[x+1,y] := r[x,y]+1; parcurge_r(x+1,y);   end;
  if (y > 1) and  (r[x,y-1]<>-1) and (r[x,y-1] > r[x,y]+1) then begin  r[x,y-1] := r[x,y]+1; parcurge_r(x,y-1);   end;
  if (y < m) and  (r[x,y+1]<>-1) and (r[x,y+1] > r[x,y]+1) then begin  r[x,y+1] := r[x,y]+1; parcurge_r(x,y+1);   end;

  if (x > 1) and  (y > 1) and (r[x-1,y-1]<>-1) and (r[x-1,y-1] > r[x,y]+1) then begin  r[x-1,y-1] := r[x,y]+1; parcurge_r(x-1,y-1);   end;
  if (x < n) and  (y > 1) and (r[x+1,y-1]<>-1) and (r[x+1,y-1] > r[x,y]+1) then begin  r[x+1,y-1] := r[x,y]+1; parcurge_r(x+1,y-1);   end;
  if (x > 1) and  (y < m) and (r[x-1,y+1]<>-1) and (r[x-1,y+1] > r[x,y]+1) then begin  r[x-1,y+1] := r[x,y]+1; parcurge_r(x-1,y+1);   end;
  if (x < n) and  (y < m) and (r[x+1,y+1]<>-1) and (r[x+1,y+1] > r[x,y]+1) then begin  r[x+1,y+1] := r[x,y]+1; parcurge_r(x+1,y+1);   end;
end;

procedure parcurge_j(x,y:integer);
begin
  if (x > 1) and (j[x-1,y]<>-1) and (j[x-1,y] > j[x,y]+1) then begin  j[x-1,y] := j[x,y]+1; parcurge_j(x-1,y);   end;
  if (x < n) and (j[x+1,y]<>-1) and (j[x+1,y] > j[x,y]+1) then begin  j[x+1,y] := j[x,y]+1; parcurge_j(x+1,y);   end;
  if (y > 1) and (j[x,y-1]<>-1) and (j[x,y-1] > j[x,y]+1) then begin  j[x,y-1] := j[x,y]+1; parcurge_j(x,y-1);   end;
  if (y < m) and (j[x,y+1]<>-1) and (j[x,y+1] > j[x,y]+1) then begin  j[x,y+1] := j[x,y]+1; parcurge_j(x,y+1);   end;

  if (x > 1) and  (y > 1) and (j[x-1,y-1]<>-1) and (j[x-1,y-1] > j[x,y]+1) then begin  j[x-1,y-1] := j[x,y]+1; parcurge_j(x-1,y-1);   end;
  if (x < n) and  (y > 1) and (j[x+1,y-1]<>-1) and (j[x+1,y-1] > j[x,y]+1) then begin  j[x+1,y-1] := j[x,y]+1; parcurge_j(x+1,y-1);   end;
  if (x > 1) and  (y < m) and (j[x-1,y+1]<>-1) and (j[x-1,y+1] > j[x,y]+1) then begin  j[x-1,y+1] := j[x,y]+1; parcurge_j(x-1,y+1);   end;
  if (x < n) and  (y < m) and (j[x+1,y+1]<>-1) and (j[x+1,y+1] > j[x,y]+1) then begin  j[x+1,y+1] := j[x,y]+1; parcurge_j(x+1,y+1);   end;
end;

begin
  assign(input,'rj.in'); reset(input);
  assign(output,'rj.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);
  for i := 1 to n do
  begin
    for h := 1 to m do
    begin
      read(x);
      case x of
        'X':begin r[i,h] := -1; j[i,h] := -1;  end;
        ' ':begin r[i,h] :=  0; j[i,h] :=  0;  end;
        'R':begin r[i,h] :=  1; j[i,h] :=  0;  rpos1 := i; rpos2 := h; end;
        'J':begin r[i,h] :=  0; j[i,h] :=  1;  jpos1 := i; jpos2 := h; end;
      end;
    end;
    readln();
  end;


  parcurge_r(rpos1,rpos2);
  parcurge_j(jpos1,jpos2);



  for i := 1 to n do
  begin
    for h := 1 to m do
    begin
      write(r[i,h],' ');
    end;
    writeln();
  end;
  writeln();
  for i := 1 to n do
  begin
    for h := 1 to m do
    begin
      write(j[i,h],' ');
    end;
    writeln();
  end;
  writeln();


  min := 999999999;

  for i := 1 to n do
  begin
    for h := 1 to m do
    begin             // mod 1   cu intoarcere
      mint := r[i,h] - j[i,h]; //if mint < 0 then mint := mint * (-1);
      if (mint mod 2 = 0)and(r[i,h] > 0)and(j[i,h] > 0) then
      begin
        if r[i,h] > j[i,h] then mint:= r[i,h] else mint := j[i,h];
        if mint < min then
        begin
          min := mint;
          pos1m := i;
          pos2m := h;
        end;
      end;

                      // mod 2   fara intoarcere
      {if (r[i,h]=j[i,h]) and(r[i,h] > 0) then
      begin
        min := r[i,h];
        pos1m := i;
        pos2m := h;
      end;    }

    end;
  end;

  writeln(min,' ',pos1m,' ',pos2m);

  close(input);
  close(output);
end.
