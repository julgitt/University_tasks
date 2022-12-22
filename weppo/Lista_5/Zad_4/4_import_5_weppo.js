"use strict";
var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", { value: true });
const _4_export_5_weppo_1 = require("./4_export_5_weppo");
const _4_export_5_weppo_2 = require("./4_export_5_weppo"); //named
//import baz from "./4_export_5_weppo"; //w tym przypadku jest bledne return value, czemu?
const MyFunctions = __importStar(require("./4_export_5_weppo")); //named
const _4_export_5_weppo_3 = __importDefault(require("./4_export_5_weppo")); //default, bez nawiasów
const _4_export_5_weppo_4 = __importDefault(require("./4_export_5_weppo")); //default to named(name = default)
MyFunctions.bar((0, _4_export_5_weppo_2.baz)(2));
(0, _4_export_5_weppo_1.bar)((0, _4_export_5_weppo_3.default)(2));
(0, _4_export_5_weppo_1.bar)((0, _4_export_5_weppo_4.default)(3));
