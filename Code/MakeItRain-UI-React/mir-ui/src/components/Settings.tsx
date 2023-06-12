import { Fieldset } from 'primereact/fieldset';
import { InputText } from 'primereact/inputtext';
import { Button } from 'primereact/button';

export default function Settings(){

    return (
        <div className="card">
            <Fieldset legend="Network">
                <h4>General</h4>
                <div className="p-inputgroup flex-1">
                        <span className="p-inputgroup-addon">
                            <i className="pi pi-globe"></i>
                        </span>
                        <InputText placeholder="Hostname" />
                    </div>
                <div className="card flex flex-wrap justify-content-center gap-2">
                    <Button label="Save" />
                    <Button label="Cancel" />
                </div>

                <h4>Wifi Settings</h4>
                <div className="card flex flex-column md:flex-row gap-3">
                    <div className="p-inputgroup flex-1">
                        <span className="p-inputgroup-addon">
                            <i className="pi pi-wifi"></i>
                        </span>
                        <InputText placeholder="Network" />
                    </div>

                    <div className="p-inputgroup flex-1">
                    <span className="p-inputgroup-addon">
                            <i className="pi pi-lock"></i>
                        </span>
                        <InputText placeholder="Password" />
                    </div>
                </div>
                <div className="card flex flex-wrap justify-content-center gap-2">
                    <Button label="Save" />
                    <Button label="Cancel" />
                </div>

                <h4>AP Mode Settings</h4>

                <div className="card flex flex-wrap justify-content-center gap-2">
                    <Button label="Save" />
                    <Button label="Cancel" />
                </div>


            </Fieldset>

            <Fieldset legend="MQTT">
                <h4>Node</h4>
                <div className="p-inputgroup flex-1">
                    <span className="p-inputgroup-addon">
                            <i className="pi pi-database"></i>
                        </span>
                        <InputText placeholder="Node" />
                    </div>

            </Fieldset>
        </div>

        
    )

}