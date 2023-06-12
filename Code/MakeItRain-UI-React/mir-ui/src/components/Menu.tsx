import {useState} from 'react';
import { TabMenu } from 'primereact/tabmenu';
import Settings from './Settings';
import Home from './Home';

export default function AppMenu() {
    const [activeIndex, setActiveIndex] = useState(0);
    const items = [
        {label: "Home", icon: "pi pi-fw pi-home"},
        {label: "Settings", icon: "pi pi-fw pi-cog"}
    ];

    return (
        <div className='card'>
            <TabMenu model={items} activeIndex={activeIndex} onTabChange={(e) => setActiveIndex(e.index)}/>
            {activeIndex === 0 && <Home />}
            {activeIndex === 1 && <Settings />}
        </div>
    )
}