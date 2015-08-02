var apar:array[0..9]of int64;
    x,y,rez,max,imax,t:int64;
    a:array[1..100003]of int64;
    e1,e2:array[0..9]of boolean;
    i,n,cf,j,cont1,cont2,scrie:longint;
    nr1,nr2:array[1..20]of shortint;
    zero,control:boolean;

begin
  assign(input,'unific.in'); reset(input);
  assign(output,'unific.out'); rewrite(output);

  readln(n);             scrie := n;
  readln(a[1]);  //citire primul element


  for i := 0 to 9 do apar[i] := 0;
  cont1 := 0; cont2 := 0;

  x := a[1];
  while x <> 0 do       //aflare cifre pt 1
  begin
    cf := x mod 10;
    x := x div 10;
    inc(apar[cf]);
  end;

  if n >1 then
  begin                   //caz n > 1
   for i := 2 to n do
   begin
     readln(a[i]); x := a[i]; y := a[i-1] ;   //citire elemente



     for j := 0 to 9 do
     begin
       e1[j]:= false; e2[j] := false;   //initializare contoare
     end;

     for j := 1  to 20 do
     begin
       nr1[j] := 0;
       nr2[j] := 0;
     end;

      while y <> 0 do            //descompunere nr anterior
      begin
        cf := y mod 10;
        y := y div 10;
        e1[cf] := true;
        inc(cont1);
        nr1[cont1] := cf;
      end;

      for j := 1 to ((cont1 div 2)+1) do
      begin
        t := nr1[j];
        nr1[j] := nr1[cont1-j+1];
        nr1[cont1-j+1] := t;
      end;

      while x <> 0 do           //descompunere nr curent
      begin
        cf := x mod 10;
        x := x div 10;
        e2[cf] := true;
        inc(apar[cf]);
        inc(cont2);
        nr2[cont2] := cf;
      end;

      rez := 0;




      zero := true;
      for j := 1 to cont1 do     //formare din primul nr
      begin
        if (e2[nr1[j]] = false)and(e1[nr1[j]]=true) then
        begin
          if nr1[j] = 0 then
          begin
            if zero = false then rez := rez*10 + nr1[j];
          end
          else
          begin
            rez := rez*10 + nr1[j];  zero := false;
          end;
        end;
      end;



      zero := true;
      for j := 1 to cont2 do        //formare din nr 2;
      begin
        if (e1[nr2[j]] = false)and(e2[nr2[j]]=true) then
        begin
          if nr2[j] = 0 then
          begin
            if zero = false then rez := rez*10 + nr2[j];
          end
          else
          begin
            rez := rez*10 + nr2[j]; zero := false;
          end;
        end;
      end;

      //writeln(rez);

      control := true;
      for j := 0 to 9 do                           //control daca x,y au aceleasi cifre
        if ((e1[j] = true)and(e2[j] = false))or((e1[j] = false)and(e2[j]=true)) then  control := false;

      if control = true then
      begin
        a[i] := -1;
        a[i-1] := -1;
        scrie := scrie - 2;
      end
      else
      begin
        a[i] := rez; a[i-1] := -1;

        dec(scrie);
      end;

    end;       //sfarsit for
  end
  else
  begin        //caz n =1
    x := a[1];
    while x <> 0 do
    begin
      cf := x mod 10;
      x := x div 10;
      inc(apar[cf]);
    end;
  end;

  max := -1;
  imax := 0;
  for j := 0 to 9 do
    if apar[j] > max then
    begin
      max := apar[j];
      imax := j;
    end;

  writeln(imax);

  if scrie > 0 then
  begin
    writeln(scrie);
    for i := 1 to n do
      if a[i] <> -1 then write(a[i],' ');
  end;



  close(input);
  close(output);
end.
