import { Component, OnInit } from '@angular/core';

@Component({
  selector: 'app-main',
  templateUrl: './main.component.html',
  styleUrls: ['./main.component.scss']
})
export class MainComponent implements OnInit {
  public display_content: string = "zones";
  constructor() { }

  ngOnInit(): void {
  }

  setView(value: string): void{
    this.display_content = value;
  }

}
