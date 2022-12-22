import {bar as named_bar} from "./4_export_5_weppo";  //named
import {baz} from "./4_export_5_weppo"; //named
//import baz from "./4_export_5_weppo"; //w tym przypadku jest bledne return value, czemu?
import * as MyFunctions from "./4_export_5_weppo"; //named
import qux from "./4_export_5_weppo"; //default, bez nawiasów
import {default as named_qux} from "./4_export_5_weppo"; //default to named(name = default)

MyFunctions.bar(baz(2));
named_bar(qux(2));
named_bar(named_qux(3));