var n,i,lna,cola,ln,col:longint;
    bufout:array[1..65000]of byte;
    c:char;

begin
  assign(input,'telefon.in'); reset(input);
  assign(output,'telefon.out'); rewrite(output);
  settextbuf(output,bufout);

  lna := 4; cola := 1;
  while not eof(input)do
  begin
    read(c);
    case c of
      '0':begin ln := 4; col := 2;  end;
      '1':begin ln := 1; col := 1;  end;
      '2':begin ln := 1; col := 2;  end;
      '3':begin ln := 1; col := 3;  end;
      '4':begin ln := 2; col := 1;  end;
      '5':begin ln := 2; col := 2;  end;
      '6':begin ln := 2; col := 3;  end;
      '7':begin ln := 3; col := 1;  end;
      '8':begin ln := 3; col := 2;  end;
      '9':begin ln := 3; col := 3;  end;
      '*':begin ln := 4; col := 1;  end;
      '#':begin ln := 4; col := 3;  end;
      else
      continue;
    end;

    //writeln(ln,'!',col,'!',lna,'!',cola);

    if lna > ln then
      write('S ',lna-ln,' ')
    else
    if lna < ln then
      write('J ',ln-lna,' ');

    if cola > col then
      write('ST ',cola-col,' ')
    else
    if cola < col then
      write('DR ',col-cola,' ');

    write('A');
    if (col<> 3) or (ln<>4) or (eof(input)=true) then write(' ');
    cola := col; lna := ln;
  end;

  if lna < 4 then write('J ',4-lna);
  if cola <> 3 then write(' ');
  if cola = 1 then write('DR 2')
  else
  if cola = 2 then write('DR 1');
  //writeln();
  close(input); close(output);
end.
